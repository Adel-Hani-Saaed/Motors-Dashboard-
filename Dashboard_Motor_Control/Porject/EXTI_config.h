/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: EXTI			  *******************/
/*************** Date: 27/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

 /*Choose INT0 Sense control(interrupt trigger)
 * Options: 1- EXTI_u8_LOW_LEVEL
 * 			2- EXTI_u8_ANY_LOGICAL_CHANGE
 * 			3- EXTI_u8_FALLING_EDGE
 * 			4- EXTI_u8_RISING_EDGE
 ****************************************/
 #define EXTI_INT0_SENSE	 EXTI_u8_FALLING_EDGE


 /*Choose INT1 Sense control(interrupt trigger)
 * Options: 1- EXTI_u8_LOW_LEVEL
 * 			2- EXTI_u8_ANY_LOGICAL_CHANGE
 * 			3- EXTI_u8_FALLING_EDGE
 * 			4- EXTI_u8_RISING_EDGE
 *******************************************/
#define EXTI_INT1_SENSE 	 EXTI_u8_RISING_EDGE


 /*Choose INT2 Sense control(interrupt trigger)
 * Options: 1- EXTI_u8_FALLING_EDGE
 * 			2- EXTI_u8_RISING_EDGE
 ********************************************/
#define EXTI_INT2_SENSE 	 EXTI_u8_FALLING_EDGE


 /*Choose INT0 , INT1 and INT2 peripheral interrupt enable(PIE) initial state
 * Options: 1- ENABLED
 * 			2- DISABLED
 ******************************************/
#define EXTI_INT0_INITIAL_STATE 	ENABLED

#define EXTI_INT1_INITIAL_STATE 	ENABLED

#define EXTI_INT2_INITIAL_STATE 	DISABLED


#endif /* EXTI_CONFIG_H_ */
