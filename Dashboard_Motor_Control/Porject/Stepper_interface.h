/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: Stepper_Motor	  *******************/
/*************** Date: 19/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_

  /* Configuration of Types */
#define STEPPER_FULL_STEP    1
#define STEPPER_HALF_STEP    0

  /* Direction the Motor  */
#define STEPPER_CLOCK_WISE       1
#define STEPPER_ANTI_CLOCK_WISE  0

  /* Stepper Pin direction */
#define STEPPER_PIN_OUTPUT   1
#define STEPPER_PIN_INPUT    0

  /* Stepper Pin State */
#define STEPPER_PIN_HIGH  	 1
#define STEPPER_PIN_LOW		 0


/* Description : this Function is to set pin direction for StepperMotor 28BYJ_48
 * \input :  nothing
 * Return  : nothing
 */
void STEPPER_voidInit( void );


/* Description : this Function is to set pin direction
 * \input :  Copy_u8StepType    			 , Range : STEPPER_FULL_STEP Or STEPPER_HALF_STEP
 *           Copy_u8Direction     		 	 , Range : STEPPER_CLOCK_WISE Or STEPPER_ANTI_CLOCK_WISE
 *           Copy_u8Speed	        		 , Range : Max of speed 2     ~   the minimum speed 10
 *           Copy_u16Degree					 , Range : From 0 to 360
 * Return  : nothing
 */
void STEPPER_voidTurnOn  ( u8 Copy_u8StepType , u8 Copy_u8Direction , u8 Copy_u8Speed , u16 Copy_u16Degree );


/* Description : this Function is turn off the stepper motor (set pins Low)
 * \input :  nothing
 * Return  : nothing
 */
void STEPPER_voidTurnOff ( void );







#endif /* STEPPER_INTERFACE_H_ */
