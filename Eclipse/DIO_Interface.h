/************************************************************/
/*************     Author : Ammar Abdelateif    *************/
/*************     Layer  : MCAL                *************/
/*************     Version: 1.00                *************/
/************************************************************/
/************************************************************/

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#define DIO_u8INPUT           0
#define DIO_u8OUTPUT          1

#define DIO_u8LOW             0
#define DIO_u8HIGH            1

#define DIO_u8PULL_UP         1
#define DIO_u8FLOAT  	      0

#define  DIO_u8PORTA     'A'
#define  DIO_u8PORTB     'B'
#define  DIO_u8PORTC     'C'
#define  DIO_u8PORTD     'D'

#define DIO_u8Pin0		0
#define DIO_u8Pin1		1
#define DIO_u8Pin2		2
#define DIO_u8Pin3		3
#define DIO_u8Pin4		4
#define DIO_u8Pin5		5
#define DIO_u8Pin6		6
#define DIO_u8Pin7		7

ES_t DIO_EnuInit(void);

ES_t DIO_EnuSetPortDirection(u8 Copy_u8PortID ,u8 Copy_u8Value);

ES_t DIO_EnuSetPortValue(u8 Copy_u8PortID ,u8 Copy_u8Value);

ES_t DIO_EnuTogPort(u8 Copy_u8PortID);

ES_t DIO_EnuGetPortValue(u8 Copy_u8PortID ,u8 * Copy_u8Value);

ES_t DIO_EnuSetPinDirection(u8 Copy_u8PortID,u8 Copy_u8PinID ,u8 Copy_u8Value);

ES_t DIO_EnuSetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Value);

ES_t DIO_EnuTogPin(u8 Copy_u8PortID,u8 Copy_u8PinID);

ES_t DIO_EnuGetPinValue(u8 Copy_u8PortID ,u8 Copy_u8PinID,u8 * Copy_u8Value);



#endif /* DIO_INTERFACE_H_ */

/************************************************************/
/************************************************************/
/*************     Author : Ammar Abdelateif    *************/
/*************     Layer  : MCAL                *************/
/*************     Version: 1.00                *************/
/*************     File   :DIO_Interface.c      *************/
/************************************************************/
/************************************************************/
