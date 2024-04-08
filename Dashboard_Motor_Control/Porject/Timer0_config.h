/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: Timer0		  *******************/
/*************** Date: 27/3/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/* 	Set Timer0 Waveform Generation Mode
 * 				Choose between
 * 					1. TIMER_NORMAL_MODE
 * 					2. TIMER_CTC_MODE
 * 					3. TIMER_FAST_PWM_MODE
 *			 		4. TIMER_PWM_PHASE_CORRECT_MODE
 */
#define TIMER0_WAVEFORM_GENERATION_MODE		TIMER_FAST_PWM_MODE


/*Set the Required Pre_scaler
				Choose between
					1- TIMER_NO_CLOCK_SOURCE
					2- TIMER_NO_PRESCALER_FACTOR
					3- TIMER_DIVISION_FACTOR_8
					4- TIMER_DIVISION_FACTOR_64
					5- TIMER_DIVISION_FACTOR_256
					6- TIMER_DIVISION_FACTOR_1024
					7- TIMER_T0_EXTERNAL_CLOCK_SOURCE_FALLING
					8- TIMER_T0_EXTERNAL_CLOCK_SOURCE_RISING
 */
#define TIMER0_PRESCALER					TIMER_DIVISION_FACTOR_8






#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

/*Set the Required Pre_load on TIMER0 Normal Mode*/
#define TIMER0_PRELOAD_VAL					192

/*Set Timer0 Overflow Interrupt
 * Choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define TIMER0_OVERFLOW_INTERRUPT			ENABLE





#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

/*Set the Required Compare Match Value on TIMER0 CTC Mode*/
#define TIMER0_CTC_VAL						0

/*Set Compare Match Output Mode
 * Choose between
 * 1. TIMER_OC_DISCONNECTED
 * 2. TIMER_OC_TOGGEL
 * 3. TIMER_OC_LOW
 * 4. TIMER_OC_HIGH
 */
#define TIMER0_OC0_MODE						TIMER_OC_DISCONNECTED

/*Set Timer0 CTC Interrupt
 * Choose between
 * 1. DISABLE
 * 2. ENABLE
 */
#define TIMER0_CTC_INTERRUPT				ENABLE



#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_PHASE_CORRECT_MODE

		/*Set the Required Compare Match Value on TIMER0 CTC Mode*/
		#define TIMER0_CTC_VAL						0

		/*Set PWM Mode
		 * Choose between
		 * 1. TIMER_OC_DISCONNECTED
		 * 2. TIMER_CLR_ON_CTC_COUNTING_UP_SET_ON_CTC_COUNTING_DWON    (Non_Interval)
		 * 3. TIMER_CLR_ON_CTC_COUNTING_DWON_SET_ON_CTC_COUNTING_UP    (Interval)
		 */
		#define TIMER0_CTC_PWM_MODE   	TIMER_CLR_ON_CTC_COUNTING_UP_SET_ON_CTC_COUNTING_DWON


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

		/*Set the Required Compare Match Value on TIMER0 CTC Mode*/
		#define TIMER0_CTC_VAL						0

		/*Set PWM Mode
		 * Choose between
		 * 1. TIMER_OC_DISCONNECTED
		 * 2. TIMER_CLR_ON_CTC_SET_ON_TOP		(Non_Interval)
		 * 3. TIMER_SET_ON_CTC_CLR_ON_TOP		(Interval)
		 */
		#define TIMER0_CTC_PWM_MODE						TIMER_CLR_ON_CTC_SET_ON_TOP

	#else
		#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"


#endif


#endif /* TIMER0_CONFIG_H_ */
