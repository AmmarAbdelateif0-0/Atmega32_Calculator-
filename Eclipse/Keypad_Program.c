/*
 * Keypad_Program.c
 *
 *  Created on: Apr 30, 2024
 *      Author: aboam
 */

#include "STD_TYPES.h"
#include "DIO_ErrorState.h"

#include "DIO_Interface.h"

#include "Keypad_Config.h"
#include "Keypad_Interface.h"
#include "Keypad_Private.h"


u8 KPD_u8GetPressedKey(void){
u8 Local_u8PressedKey=Key_NPresedKey;

static u8 Local_u8KPDColumArrPins[NUM_COLUMS]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
static u8 Local_u8KPDColumArrPort[NUM_COLUMS]={KPD_COLUMN0_PORT,KPD_COLUMN1_PORT,KPD_COLUMN2_PORT,KPD_COLUMN3_PORT};

static u8 Local_u8KPDRowsArrPins[NUM_COLUMS]= {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};
static u8 Local_u8KPDRowsArrPort[NUM_COLUMS]= {KPD_ROW0_PORT,KPD_ROW1_PORT,KPD_ROW2_PORT,KPD_ROW3_PORT};

u8 Local_u8CounterRows=0;
u8 Local_u8CounterColums=0;

u8 Local_u8PinState;


u8 Local_u8KPDArr[NUM_ROWS][NUM_COLUMS]=KPD_ARR_VAL;
for( Local_u8CounterColums=0; Local_u8CounterColums<NUM_COLUMS; Local_u8CounterColums++)
{
	DIO_EnuSetPinValue(Local_u8KPDColumArrPort[Local_u8CounterColums],Local_u8KPDColumArrPins[Local_u8CounterColums],DIO_u8LOW);

	for( Local_u8CounterRows=0; Local_u8CounterRows<NUM_ROWS; Local_u8CounterRows++)
		{
			DIO_EnuGetPinValue(Local_u8KPDRowsArrPort[Local_u8CounterRows],Local_u8KPDRowsArrPins[Local_u8CounterRows],&Local_u8PinState);

			if(DIO_u8LOW==Local_u8PinState){
				Local_u8PressedKey=Local_u8KPDArr[Local_u8CounterRows][Local_u8CounterColums];

				/* Polling busy Waiting until event */
				while(DIO_u8LOW==Local_u8PinState){
					DIO_EnuGetPinValue(Local_u8KPDRowsArrPort[Local_u8CounterRows],Local_u8KPDRowsArrPins[Local_u8CounterRows],&Local_u8PinState);

				}
				return Local_u8PressedKey;
			}
		}
	DIO_EnuSetPinValue(Local_u8KPDColumArrPort[Local_u8CounterColums],Local_u8KPDColumArrPins[Local_u8CounterColums],DIO_u8HIGH );

}
return Local_u8PressedKey;
}
