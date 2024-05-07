/*
 * Keypad_Config.h
 *
 *  Created on: Apr 30, 2024
 *      Author: aboam
 */

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define NUM_ROWS   		4

#define NUM_COLUMS 		4

#define Key_NPresedKey       0xff

#define KPD_ARR_VAL {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'o','0','=','+'}}

#define KPD_ROW0_PIN   	    DIO_u8Pin0
#define KPD_ROW0_PORT		DIO_u8PORTA

#define KPD_ROW1_PIN		DIO_u8Pin1
#define KPD_ROW1_PORT		DIO_u8PORTA


#define KPD_ROW2_PIN		DIO_u8Pin2
#define KPD_ROW2_PORT		DIO_u8PORTA

#define KPD_ROW3_PIN		DIO_u8Pin3
#define KPD_ROW3_PORT		DIO_u8PORTA

#define KPD_COLUMN0_PIN 	DIO_u8Pin4
#define KPD_COLUMN0_PORT	DIO_u8PORTA

#define KPD_COLUMN1_PIN		DIO_u8Pin5
#define KPD_COLUMN1_PORT	DIO_u8PORTA

#define KPD_COLUMN2_PIN		DIO_u8Pin6
#define KPD_COLUMN2_PORT	DIO_u8PORTA

#define KPD_COLUMN3_PIN		DIO_u8Pin7
#define KPD_COLUMN3_PORT	DIO_u8PORTA

#endif /* KEYPAD_CONFIG_H_ */
