/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: Timer1		  *******************/
/*************** Date: 31/3/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


/* Description : this Function is to set the Timer1
 * \input  : nothing
 * Return  : nothing
 */
void TIMER1_voidInit(void);


/* Description : this Function is to set the value of pre_load in register TCNT0_REG
 * \input  : Copy_u16PreloadValue       Range : 0 ~ 65536
 * Return  : nothing
 */
void TIMER1_voidSetPreloadValue (u16 Copy_u16PreloadValue) ;



/* Description : this Function is to set the value of TOP in register ICR
 * \input  : Copy_u16PreloadValue       Range : 0 ~ 65536
 * Return  : nothing
 */
void TIMER1_voidSetICR1 (u16 Copy_u16ICR1) ;


/* Description : this Function is to set the value of CTC Value in register OCR1A & OCR1B
 * \input  : Copy_u16PreloadValue       Range : 0 ~ 65536
 * Return  : nothing
 */
void TIMER1_voidSetValueCompMatchChannel_A (u16 Copy_u16CTCA);
void TIMER1_voidSetValueCompMatchChannel_B (u16 Copy_u16CTCB);

#endif /* TIMER1_INTERFACE_H_ */
