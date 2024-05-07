/************************************************************/
/*************     Author : Ammar Abdelateif    *************/
/*************     Layer  : MCAL                *************/
/*************     Version: 1.00                *************/
/************************************************************/
/************************************************************/

/**************************** include ******************************************/

#include"STD_TYPES.h"
#include"DIO_ErrorState.h"
#include"BIT_MATH.h"

#include"DIO_Private.h"
#include"DIO_Config.h"
/*******************************************************************************/

/*************************** INITAL DIO ****************************************/
ES_t DIO_EnuInit(void){

	u8 Local_u8Errorstate=ES_NOK;

	DDRA = CONC(PA_Pin7_Dir,PA_Pin6_Dir,PA_Pin5_Dir,PA_Pin4_Dir,PA_Pin3_Dir,PA_Pin2_Dir,PA_Pin1_Dir,PA_Pin0_Dir);
	DDRB = CONC(PB_Pin7_Dir,PB_Pin6_Dir,PB_Pin5_Dir,PB_Pin4_Dir,PB_Pin3_Dir,PB_Pin2_Dir,PB_Pin1_Dir,PB_Pin0_Dir);
	DDRC = CONC(PC_Pin7_Dir,PC_Pin6_Dir,PC_Pin5_Dir,PC_Pin4_Dir,PC_Pin3_Dir,PC_Pin2_Dir,PC_Pin1_Dir,PC_Pin0_Dir);
	DDRD = CONC(PD_Pin7_Dir,PD_Pin6_Dir,PD_Pin5_Dir,PD_Pin4_Dir,PD_Pin3_Dir,PD_Pin2_Dir,PD_Pin1_Dir,PD_Pin0_Dir);


	PORTA = CONC(PA_Pin7_VAL,PA_Pin6_VAL,PA_Pin5_VAL,PA_Pin4_VAL,PA_Pin3_VAL,PA_Pin2_VAL,PA_Pin1_VAL,PA_Pin0_VAL);
	PORTB = CONC(PB_Pin7_VAL,PB_Pin6_VAL,PB_Pin5_VAL,PB_Pin4_VAL,PB_Pin3_VAL,PB_Pin2_VAL,PB_Pin1_VAL,PB_Pin0_VAL);
	PORTC = CONC(PC_Pin7_VAL,PC_Pin6_VAL,PC_Pin5_VAL,PC_Pin4_VAL,PC_Pin3_VAL,PC_Pin2_VAL,PC_Pin1_VAL,PC_Pin0_VAL);
	PORTD = CONC(PD_Pin7_VAL,PD_Pin6_VAL,PD_Pin5_VAL,PD_Pin4_VAL,PD_Pin3_VAL,PD_Pin2_VAL,PD_Pin1_VAL,PD_Pin0_VAL);

	Local_u8Errorstate=ES_OK;

	return Local_u8Errorstate;
}

/*******************************************************************************/

/*************************** CONTROL PORTS *************************************/
ES_t DIO_EnuSetPortDirection(u8 Copy_u8PortID ,u8 Copy_u8Value){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case 'A':
					DDRA=Copy_u8Value;
					break;
			case 'B':
					DDRB=Copy_u8Value;
					break;
			case 'C':
					DDRC=Copy_u8Value;
					break;
			case 'D':
					DDRD=Copy_u8Value;
					break;
		}
		Local_u8Errorstate=ES_OK;
	}
	else
	{
		Local_u8Errorstate=ES_OUT_OF_RANGE;
	}

	return Local_u8Errorstate;
}

/*******************************************************************************/

ES_t DIO_EnuSetPortValue(u8 Copy_u8PortID ,u8 Copy_u8Value){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case 'A':
					PORTA=Copy_u8Value;
					break;
			case 'B':
					PORTB=Copy_u8Value;
					break;
			case 'C':
					PORTC=Copy_u8Value;
					break;
			case 'D':
					PORTD=Copy_u8Value;
					break;
		}
		Local_u8Errorstate=ES_OK;
	}
	else
	{
		Local_u8Errorstate=ES_OUT_OF_RANGE;
	}

	return Local_u8Errorstate;
}

/*******************************************************************************/

ES_t DIO_EnuTogPort(u8 Copy_u8PortID){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8PortID<=DIO_PORTD)
	{
		switch(Copy_u8PortID)
		{
			case 'A':
					PORTA=~PORTA;
					break;
			case 'B':
					PORTB=~PORTB;
					break;
			case 'C':
					PORTC=~PORTC;
					break;
			case 'D':
					PORTD=~PORTD;
					break;
		}
		Local_u8Errorstate=ES_OK;
	}
	else
	{
		Local_u8Errorstate=ES_OUT_OF_RANGE;
	}

	return Local_u8Errorstate;
}

/*******************************************************************************/

ES_t DIO_EnuGetPortValue(u8 Copy_u8PortID ,u8 * Copy_u8Value){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8Value!=NULL)
	{
		if(Copy_u8PortID<=DIO_PORTD){
				 switch(Copy_u8PortID)
				 {
					case 'A':
							*Copy_u8Value=PINA;
							break;
					case 'B':
							*Copy_u8Value=PINB;
							break;
					case 'C':
							*Copy_u8Value=PINC;
							break;
					case 'D':
							*Copy_u8Value=PIND;
							break;
				 }
				 Local_u8Errorstate=ES_OK;
			}
		else{
				Local_u8Errorstate=ES_OUT_OF_RANGE;
		    }
	}
	else
	{
		Local_u8Errorstate=ES_PNULL;
	}

	return Local_u8Errorstate;
}

/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


/*************************** CONTROL PINS *************************************/
ES_t DIO_EnuSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID ,u8 Copy_u8Value){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8PortID<=DIO_PORTD && Copy_u8PinID<=DIO_Pin7 && Copy_u8Value<=OUTPUT)
		{
					 switch(Copy_u8PortID)
					 {
						case 'A':
								CLR_BIT(DDRA,Copy_u8PinID);
								DDRA|=(Copy_u8Value<<Copy_u8PinID);
								break;
						case 'B':
								CLR_BIT(DDRB,Copy_u8PinID);
								DDRB|=(Copy_u8Value<<Copy_u8PinID);
								break;
						case 'C':
								CLR_BIT(DDRC,Copy_u8PinID);
								DDRC|=(Copy_u8Value<<Copy_u8PinID);
								break;
						case 'D':
								CLR_BIT(DDRD,Copy_u8PinID);
								DDRD|=(Copy_u8Value<<Copy_u8PinID);
								break;
					 }
					 Local_u8Errorstate=ES_OK;
			}
	else {
				Local_u8Errorstate=ES_OUT_OF_RANGE;
	    }

	return Local_u8Errorstate;
}

/*******************************************************************************/

ES_t DIO_EnuSetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Value){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8PortID<=DIO_PORTD && Copy_u8PinID<=DIO_Pin7 && Copy_u8Value<=OUTPUT)
		{
					 switch(Copy_u8PortID)
					 {
						case 'A':
								CLR_BIT(PORTA,Copy_u8PinID);
								PORTA|=(Copy_u8Value<<Copy_u8PinID);
								break;
						case 'B':
								CLR_BIT(PORTB,Copy_u8PinID);
								PORTB|=(Copy_u8Value<<Copy_u8PinID);
								break;
						case 'C':
								CLR_BIT(PORTC,Copy_u8PinID);
								PORTC|=(Copy_u8Value<<Copy_u8PinID);
								break;
						case 'D':
								CLR_BIT(PORTD,Copy_u8PinID);
								PORTD|=(Copy_u8Value<<Copy_u8PinID);
								break;
					 }
				Local_u8Errorstate=ES_OK;
			}
	else {
				Local_u8Errorstate=ES_OUT_OF_RANGE;
	    }


	return Local_u8Errorstate;
}

/*******************************************************************************/

ES_t DIO_EnuTogPin(u8 Copy_u8PortID,u8 Copy_u8PinID){
	u8 Local_u8Errorstate=ES_NOK;
	if(Copy_u8PortID<=DIO_PORTD && Copy_u8PinID<=DIO_Pin7)
		{
					 switch(Copy_u8PortID)
					 {
						case 'A':
								TOG_BIT(PORTA,Copy_u8PinID);
								break;
						case 'B':
								TOG_BIT(PORTB,Copy_u8PinID);
								break;
						case 'C':
								TOG_BIT(PORTC,Copy_u8PinID);
								break;
						case 'D':
								TOG_BIT(PORTD,Copy_u8PinID);
								break;
					 }
			Local_u8Errorstate=ES_OK;
		}
	else{
				Local_u8Errorstate=ES_OUT_OF_RANGE;
	    }


	return Local_u8Errorstate;
}

/*******************************************************************************/

ES_t DIO_EnuGetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID,u8 * Copy_u8Value){

	u8 Local_u8Errorstate=ES_NOK;

	if(Copy_u8Value!=NULL)
	{
		if(Copy_u8PortID<=DIO_PORTD && Copy_u8PinID<=DIO_Pin7){
				 switch(Copy_u8PortID)
				 {
					case 'A':
						*Copy_u8Value=GET_BIT(PINA,Copy_u8PinID);
						break;
					case 'B':
						*Copy_u8Value=GET_BIT(PINB,Copy_u8PinID);
						break;
					case 'C':
						*Copy_u8Value=GET_BIT(PINC,Copy_u8PinID);
						break;
					case 'D':
						*Copy_u8Value=GET_BIT(PIND,Copy_u8PinID);
						break;
				 }
				 Local_u8Errorstate=ES_OK;
			}
		else{
				Local_u8Errorstate=ES_OUT_OF_RANGE;
		    }
	}
	else
	{
		Local_u8Errorstate=ES_PNULL;
	}

	return Local_u8Errorstate;
}

/************************************************************/
/************************************************************/
/*************     Author : Ammar Abdelateif    *************/
/*************     Layer  : MCAL                *************/
/*************     Version: 1.00                *************/
/*************     File   :DIO_program.c        *************/
/************************************************************/
/************************************************************/



