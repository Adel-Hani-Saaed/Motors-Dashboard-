/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: Timer0		  *******************/
/*************** Date: 27/3/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_


#define TCCR0_REG 			*((volatile u8*)0x53)		/*Timer/Counter control register*/

#define TCCR0_FOC0			7							/*Force Output compare*/
#define TCCR0_WGM00			6							/*Wave for generation mode  BIT_1*/
#define	TCCR0_COM01			5 							/*Compare match output mode BIT_1*/
#define	TCCR0_COM00			4							/*Compare match output mode BIT_2*/
#define TCCR0_WGM01			3							/*Wave for generation mode  BIT_2*/
#define TCCR0_CS02			2							/*Clock Selection Bit_3*/
#define TCCR0_CS01			1							/*Clock Selection Bit_2*/
#define TCCR0_CS00			0							/*Clock Selection Bit_1*/


#define TCNT0_REG			*((volatile u8*)0x52)		/*Timer/Counter register (overflow) */

#define OCR0_REG			*((volatile u8*)0x5C)		/*Output compare match Register*/

#define TIMSK_REG			*((volatile u8*)0x59)		/*Timer/Counter interrupt mask register*/

#define TIMSK_TOIE0			0							/*Timer/Counter Overflow Mode interrupt Enable Bit*/
#define TIMSK_OCIE0			1							/*Timer/Counter CTC Mode interrupt Enable Bit*/




#endif /* TIMER0_REGISTER_H_ */
