/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: Timer0		  *******************/
/*************** Date: 27/3/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_


#define TIMER_PRESCALER_MASK					     0b11111000 /* This Value also could use for bit masking */

#define TIMER_NO_CLOCK_SOURCE                        0
#define TIMER_NO_PRESCALER_FACTOR                    1
#define TIMER_DIVISION_FACTOR_8                      2
#define TIMER_DIVISION_FACTOR_64                     3
#define TIMER_DIVISION_FACTOR_256                    4
#define TIMER_DIVISION_FACTOR_1024                   5
#define TIMER_T0_EXTERNAL_CLOCK_SOURCE_FALLING       6
#define TIMER_T0_EXTERNAL_CLOCK_SOURCE_RISING        7

/*Fast PWM*/
#define TIMER_OC_DISCONNECTED     					 1
#define TIMER_CLR_ON_CTC_SET_ON_TOP					 2
#define TIMER_SET_ON_CTC_CLR_ON_TOP					 3

/*Phase Correct*/
#define TIMER_OC_DISCONNECTED     					 					 1
#define TIMER_CLR_ON_CTC_COUNTING_UP_SET_ON_CTC_COUNTING_DWON			 2
#define TIMER_CLR_ON_CTC_COUNTING_DWON_SET_ON_CTC_COUNTING_UP							         3

#define DISABLE						                 0
#define ENABLE						                 1

#define TIMER_NORMAL_MODE						     0
#define TIMER_PWM_PHASE_CORRECT_MODE			     1
#define TIMER_CTC_MODE							     2
#define TIMER_FAST_PWM_MODE						     3

#define TIMER_OC_DISCONNECTED					     0
#define TIMER_OC_TOGGEL							     1
#define TIMER_OC_LOW							     2
#define TIMER_OC_HIGH							     3


#endif /* TIMER0_PRIVATE_H_ */
