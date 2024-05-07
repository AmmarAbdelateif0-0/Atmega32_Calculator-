/*
 * CLCD_Program.c
 *
 *  Created on: Apr 23, 2024
 *      Author: aboam
 */

#include"STD_TYPES.h"
#include "DIO_ErrorState.h"

#include"DIO_Interface.h"

#include "CLCD_Interface.h"
#include "CLCD_Config.h"
#include "CLCD_Private.h"

#include <util/delay.h>

ES_t CLCD_EnuSendCommand(u8 copy_u8Command)
{
	u8 Local_u8Errorstate=ES_NOK;
	/*SET RS PIN TO LOW FOR COMMAND MODE*/
	DIO_EnuSetPinValue(RS_PORT,RS_PIN,DIO_u8LOW);
	/*SET RW PIN TO LOW FOR WRITE MODE*/
	DIO_EnuSetPinValue(RW_PORT,RW_PIN,DIO_u8LOW);
	/* SEND COMMAND FOR DATA PINS*/
#if DATA_PINS_PORT==NO
	DIO_EnuSetPinValue(D7_PORT,D7_PIN, ( (copy_u8Command>>7) &1 ));
	DIO_EnuSetPinValue(D6_PORT,D6_PIN, ( (copy_u8Command>>6) &1 ));
	DIO_EnuSetPinValue(D5_PORT,D5_PIN, ( (copy_u8Command>>5) &1 ));
	DIO_EnuSetPinValue(D4_PORT,D4_PIN, ( (copy_u8Command>>4) &1 ));
	DIO_EnuSetPinValue(D3_PORT,D3_PIN, ( (copy_u8Command>>3) &1 ));
	DIO_EnuSetPinValue(D2_PORT,D2_PIN, ( (copy_u8Command>>2) &1 ));
	DIO_EnuSetPinValue(D1_PORT,D1_PIN, ( (copy_u8Command>>1) &1 ));
	DIO_EnuSetPinValue(D0_PORT,D0_PIN, ( (copy_u8Command>>0) &1 ));
#elif ( ( DATA_PINS_PORT==DIO_u8PORTA ) || ( DATA_PINS_PORT==DIO_u8PORTB ) || ( DATA_PINS_PORT==DIO_u8PORTC ) || ( DATA_PINS_PORT==DIO_u8PORTD ) )
	DIO_EnuSetPortValue(DATA_PINS_PORT,copy_u8Command);

#else
	Local_u8Errorstate=ES_OUT_OF_RANGE;
#error "DATA_PINS_PORT OUT OF RANGE PLEASE CHECK AGAIN"
#endif

	/*Send Enable Pulse*/

	DIO_EnuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
	_delay_ms(2);

	DIO_EnuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);

	return Local_u8Errorstate;
}


ES_t CLCD_EnuSendData(u8 copy_u8Data)
{
	u8 Local_u8Errorstate=ES_NOK;
	/*SET RS PIN TO LOW FOR DATA MODE*/
	DIO_EnuSetPinValue(RS_PORT,RS_PIN,DIO_u8HIGH);
	/*SET RW PIN TO LOW FOR WRITE MODE*/
	DIO_EnuSetPinValue(RW_PORT,RW_PIN,DIO_u8LOW);
	/* SEND COMMAND FOR DATA PINS*/

	DIO_EnuSetPinValue(D7_PORT,D7_PIN, ( (copy_u8Data>>7) &1 ));
	DIO_EnuSetPinValue(D6_PORT,D6_PIN, ( (copy_u8Data>>6) &1 ));
	DIO_EnuSetPinValue(D5_PORT,D5_PIN, ( (copy_u8Data>>5) &1 ));
	DIO_EnuSetPinValue(D4_PORT,D4_PIN, ( (copy_u8Data>>4) &1 ));
	DIO_EnuSetPinValue(D3_PORT,D3_PIN, ( (copy_u8Data>>3) &1 ));
	DIO_EnuSetPinValue(D2_PORT,D2_PIN, ( (copy_u8Data>>2) &1 ));
	DIO_EnuSetPinValue(D1_PORT,D1_PIN, ( (copy_u8Data>>1) &1 ));
	DIO_EnuSetPinValue(D0_PORT,D0_PIN, ( (copy_u8Data>>0) &1 ));


	/*Send Enable Pulse*/
	DIO_EnuSetPinValue(EN_PORT,EN_PIN,DIO_u8HIGH);
	_delay_ms(2);
	DIO_EnuSetPinValue(EN_PORT,EN_PIN,DIO_u8LOW);

	return Local_u8Errorstate;
}


ES_t CLCD_EnuInit(void)
{
	u8 Local_u8Errorstate=ES_NOK;

	/*Wait for more than 30 ms*/
	 _delay_ms(40);
	/*Function Set Command : 2 lines , 5*8 Font Size */
	  CLCD_EnuSendCommand(0X38);
	/*Wait for more than 39 ms*/
	 //_delay_ms(1);
	/*Display on / off Control : display enable , enable cursor ,enable blink cursor.( send commend =0X0F )*/
	 CLCD_EnuSendCommand(0X0C);
	/*Clear Display */
	 CLCD_EnuSendCommand(0X01);

	 CLCD_EnuSendCommand(0X06 );


	return Local_u8Errorstate;
}

ES_t CLCD_EnuSendString(const char* Copy_PCstring){
	u8 Local_u8Errorstate=ES_NOK;
	u8 Counter=0;
	if(NULL!=Copy_PCstring)
	{
		Local_u8Errorstate=ES_OK;
		while(Copy_PCstring[Counter]!='\0'){
			CLCD_EnuSendData(Copy_PCstring[Counter]);
			Counter++;
		}
	}
	else{
		Local_u8Errorstate=ES_PNULL;
	}

	return Local_u8Errorstate;


}


ES_t CLCD_EnuGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos){
	u8 Local_u8Errorstate=ES_NOK;
	u8 Local_u8Address=0;
	if(Copy_u8XPos==0){
		/*Location is at First Line*/
		Local_u8Address=Copy_u8YPos;
		Local_u8Errorstate=ES_OK;
	}
	else if(Copy_u8XPos==1){
		/*Location is at Second Line*/

		Local_u8Address=0X40+Copy_u8YPos;
		Local_u8Errorstate=ES_OK;
	}
	else{
		Local_u8Errorstate=ES_OUT_OF_RANGE;
	}
	/*Set bit number 7 for set DDRAM Address command then send the command*/

	CLCD_EnuSendCommand(Local_u8Address+0X80);


	return  Local_u8Errorstate;
}

ES_t CLCD_EnuWriteSpeacialCharacter(u8* Copy_pu8Pattern ,u8 Copy_u8PatternNumber ,u8 Copy_u8XPos ,u8 Copy_u8YPos){
	u8 Local_u8Errorstate=ES_NOK;

	u8 Local_u8Iterator=0;
	u8 Local_u8CGRAMAddress=0;
	/*Calculate the CGRam address whose each block is 9 byte*/

	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;

	/*send CG RAM address command to LCD , with setting bit 6 ,clearing bit 7 */

	CLCD_EnuSendCommand(Local_u8CGRAMAddress+0X40);

	/*Write the Pattern into CG Ram*/

	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++){
		CLCD_EnuSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/*Go Back to the DDRAM to display the Pattern*/

	CLCD_EnuGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*Display the Pattern Written in the CG RAM*/

	CLCD_EnuSendData(Copy_u8PatternNumber);

	return  Local_u8Errorstate;
}


ES_t CLCD_EnuClearDisplay(void){
	u8 Local_u8Errorstate=ES_NOK;
	/*Clear Display */
	 CLCD_EnuSendCommand(0X01);
	return  Local_u8Errorstate;

}


ES_t CLCD_EnuWriteNumber(f64 Copy_u8Number)
{
	u8 Local_u8Errorstate=ES_NOK;
	u8 Local_u8ArrNum[20];
	u8 Local_u8Counter=0;

	if(Copy_u8Number<0){
		CLCD_EnuSendData('-');
		Copy_u8Number*=-1;
	}
	int x=Copy_u8Number;
	int z=(Copy_u8Number-x)*100000;
	if(z==0){

		x=Copy_u8Number;
		while(x!=0){
			Local_u8ArrNum[Local_u8Counter]=x%10;
			x/=10;
			Local_u8Counter++;
		}
		for(s8 i=Local_u8Counter-1;i>=0;i--){
			CLCD_EnuSendData(Local_u8ArrNum[i]+'0');
		}
	}
	else{
		// part integer
		while(x!=0){
			Local_u8ArrNum[Local_u8Counter]=x%10;
			x/=10;
			Local_u8Counter++;
		}
		for(s8 i=Local_u8Counter-1;i>=0;i--){
			CLCD_EnuSendData(Local_u8ArrNum[i]+'0');
			Local_u8ArrNum[i]=0;
		}
		// part float
		CLCD_EnuSendData('.');
		Local_u8Counter=0;

		while(z!=0){
			Local_u8ArrNum[Local_u8Counter]=z%10;
			z/=10;
			Local_u8Counter++;
		}
		for(s8 i=Local_u8Counter-1;i>=0;i--){
			CLCD_EnuSendData(Local_u8ArrNum[i]+'0');
		}
	}


	return  Local_u8Errorstate;
}
