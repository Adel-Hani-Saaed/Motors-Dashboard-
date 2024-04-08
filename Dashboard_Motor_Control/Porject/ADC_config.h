/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: ADC			  *******************/
/*************** Date: 10/3/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*
  Selection Options:-
 	 	 1-ADC_AREF  			 // any volt support the AREF
 	 	 2-ADC_AVCC 			 // 5V
 	 	 3-ADC_INTERNAL_2_56 	 // Internal AREF pin connected with 2.56 volt

 */
#define ADC_VOLT_REFRE  ADC_AVCC

/*
  Selection Options ADC Adjustment :-
 	 	 1- ADC_TEN_BITS_MOOD      		 //RIGHT_ADJUSTMENT
 	 	 2- ADC_EIGHT_BITS_MOOD      	 //LEFT_ADJUSTMENT
 */
#define ADC_ADJUSTMENT_READING 		ADC_TEN_BITS_MOOD

/*
  Selection Options:-
			 1-DIV_BY_2
			 2-DIV_BY_4
			 3-DIV_BY_8
			 4-DIV_BY_16
			 5-DIV_BY_28
			 6-DIV_BY_64
			 7-DIV_BY_128
 */
#define	 ADC_PRESCALLER			DIV_BY_128



/*	Conversion Mood
	Selection Options:-
 	 	 1-SINGLE_CONVERSION
 	 	 2-TURO_TRIGGER
*/
#define ADC_CONVERSION_MOOD		SINGLE_CONVERSION



/*	ADC Auto trigger Source work in  TURO_TRIGGER MOOD
	Selection Options:-
 	 	 1-FREE_RUNNIG
 	 	 2-ANALOG_COMPARATOR
 	 	 3-EXTI_REQUEST_0
 	 	 4-TIMER_0_COMPARE_MATCH
 	 	 5-TIMER_0_OVERFLOW
 	 	 6-TIMER_1_COMPARE_MATCH_B
 	 	 7-TIMER_1_OVERFLOW
 	 	 8-TIMER_1_CAPTURE_EVENT
*/

#define ADC_AUTO_TRIGGER 	FREE_RUNNIG


/*	ADC Auto triggerSelection Channel
	Selection Options:-
		1-ADC_CHANNEL_A0
		2-ADC_CHANNEL_A1
		3-ADC_CHANNEL_A2
		4-ADC_CHANNEL_A3
		5-ADC_CHANNEL_A4
		6-ADC_CHANNEL_A5
		7-ADC_CHANNEL_A6
		8-ADC_CHANNEL_A7
*/
#define SET_CHANNLE_AUTO_TRIGGER	ADC_CHANNEL_A0

#define ADC_u32TIMEOUT 		50000

#endif /* ADC_CONFIG_H_ */
