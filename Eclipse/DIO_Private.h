/************************************************************/
/*************     Author : Ammar Abdelateif    *************/
/*************     Layer  : MCAL                *************/
/*************     Version: 1.00                *************/
/************************************************************/
/************************************************************/

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#define INPUT           0
#define OUTPUT          1

#define LOW             0
#define HIGH            1
#define PULL_UP         1
#define FLOAT  	        0

#define  DIO_MASK_BIT   1

#define  DIO_PORTA     'A'
#define  DIO_PORTB     'B'
#define  DIO_PORTC     'C'
#define  DIO_PORTD     'D'

#define DIO_Pin0		0
#define DIO_Pin1		1
#define DIO_Pin2		2
#define DIO_Pin3		3
#define DIO_Pin4		4
#define DIO_Pin5		5
#define DIO_Pin6		6
#define DIO_Pin7		7

/*************     REGISTER A         *************/

#define PORTA (*((volatile u8*)0X3B))
#define DDRA  (*((volatile u8*)0X3A))
#define PINA  (*((volatile u8*)0X39))

/**************************************************/


/*************     REGISTER B         *************/

#define PORTB (*((volatile u8*)0X38))
#define DDRB  (*((volatile u8*)0X37))
#define PINB  (*((volatile u8*)0X36))

/**************************************************/


/*************     REGISTER C         *************/

#define PORTC (*((volatile u8*)0X35))
#define DDRC  (*((volatile u8*)0X34))
#define PINC  (*((volatile u8*)0X33))

/**************************************************/


/*************     REGISTER D         *************/

#define PORTD (*((volatile u8*)0X32))
#define DDRD  (*((volatile u8*)0X31))
#define PIND  (*((volatile u8*)0X30))

/**************************************************/

#define CONC_Help(b7,b6,b5,b4,b3,b2,b1,b0)  0b##b7##b6##b5##b4##b3##b2##b1##b0
#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)       CONC_Help(b7,b6,b5,b4,b3,b2,b1,b0)

#endif /* DIO_PRIVATE_H_ */

/************************************************************/
/************************************************************/
/*************     Author : Ammar Abdelateif    *************/
/*************     Layer  : MCAL                *************/
/*************     Version: 1.00                *************/
/*************     File   :DIO_Private.c        *************/
/************************************************************/
/************************************************************/
