/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: EXTI			  *******************/
/*************** Date: 27/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_



/********************Macros in Enable And Disable (EXTI_u8ExtIEnable)function****************/
#define EXTI_u8_INT0 					0
#define EXTI_u8_INT1		    		1
#define EXTI_u8_INT2 					2

/*Hint imPorrant: not Start from 0 because the 0 is false and if in configuration
 *  enter any thing wrong will selected 0 false and choice falling*/

#define EXTI_u8_FALLING_EDGE   			1
#define EXTI_u8_RISING_EDGE 			2
#define EXTI_u8_ANY_LOGICAL_CHANGE 		3
#define EXTI_u8_LOW_LEVEL 				4


/****************************************************************/
/* The Driver Configuration Type ********************************/
/*								1- Prebuild Configuration.		*/
/* 								2- Postbuild  Configuration.	*/
/****************************************************************/


/**************************************************************************/
/*********************** First Prebuild Configuration *********************/
/**************************************************************************/

/**************************************************************************************/
/*Description: Initiate Required Bit to request an interrupt on INT0 Pin
* 			Inputs: No Inputs
* 			Outputs: No Outputs
*
**************************************************************************************/
void EXTI_voidINT0Init (void);

/**************************************************************************************/
/*Description: Initiate Required Bit to request an interrupt on INT0 Pin
* 			Inputs: No Inputs
* 			Outputs: No Outputs
*/
/**************************************************************************************/
void EXTI_voidINT1Init (void);

/**************************************************************************************/
/*Description: Initiate Required Bit to request an interrupt on INT0 Pin
* 			Inputs: No Inputs
* 			Outputs: No Outputs
*/
/**************************************************************************************/
void EXTI_voidINT2Init (void);

/**************************************************************************/
/********************* Second Postbuild Configuration *********************/
/**************************************************************************/
/**************************************************************************************/
/*Description: Change sense control of the require Interrupt
* Inputs: 	1- Copy_u8IntNumber : the required interrupt number to change sense control
* 					Options: 1- EXTI_INT0
* 							 2- EXTI_INT1
*							 3- EXTI_INT2
*
*				 2- Copy_u8IntEdgeSrc: The required sense control for the external interrupt
* 					Options: 1- EXTI_u8_LOW_LEVEL
* 							 2- EXTI_u8_ANY_LOGICAL_CHANGE
*							 3- EXTI_u8_FALLING_EDGE
*							 4- EXTI_u8_RISING_EDGE
*
* Outputs: 	Error state
*					Options: 1- OK
*							 2- NOK
************************************************************************************/
u8 EXTI_u8ExtIEnable (u8 Copy_u8IntNum, u8 Copy_u8IntEdgeSrc);




/***************************************************************************************/
/*Description: Disable the require Interrupt
 *Inputs: 	1- Copy_u8IntNumber : the required interrupt number to be disabled
 *					Options: 1- EXTI_INT0
 *							 2- EXTI_INT1
 *							 3- EXTI_INT2
 *Outputs: 	Error state
 *					Options: 1- OK
 *							 2- NOK
 ***************************************************************************************/
u8 EXTI_u8ExtIDisable (u8 Copy_u8IntNum);




/***************************************************************************************/
/*Description: Registering function
 *Inputs: 	1- void (*Copy_pvInt0Func)(void) :the pointer to function input
 *
 *Outputs: 	Error state
 *					Options: 1- OK
 *							 2- NOK
 ***************************************************************************************/
u8 EXTI_u8ExtISetCallBackINT0 (void (*Copy_pvInt0Func)(void));

u8 EXTI_u8ExtISetCallBackINT1 (void (*Copy_pvInt1Func)(void));

u8 EXTI_u8ExtISetCallBackINT2 (void (*Copy_pvInt2Func)(void));








#endif  /* EXTI_INTERFACE_H_ */
