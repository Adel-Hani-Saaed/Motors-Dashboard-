/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: ADC			  *******************/
/*************** Date: 10/3/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/* Bit Masking Macros  */
/*Bits masking the pre_scaler ensure the bits before the masking must the zeros */
#define ADC_PRESCALERMASK  		 0b11111000

/*Bits masking the selection channel ensure the bits before the masking must the zeros */
#define ADC_CHANNELMASK   		 0b11100000

/*Bits masking the selection Auto Trigger Mode ensure the bits before the masking must the zeros */
#define ADC_AUTO_TRIGGER_MASK	 0b00011111

/*The value in Data_sheet from Pre_Scaler*/
#define DIV_BY_2     	    0
#define DIV_BY_4     	    2
#define DIV_BY_8     	    3
#define DIV_BY_16    	    4
#define DIV_BY_28    	    5
#define DIV_BY_64    	    6
#define DIV_BY_128   	    7


/*The value in Data_sheet from Selection Auto Trigger*/

#define FREE_RUNNIG              0b00000000
#define ANALOG_COMPARATOR        0b00100000
#define EXTI_REQUEST_0           0b01000000
#define TIMER_0_COMPARE_MATCH    0b01100000
#define TIMER_0_OVERFLOW         0b10000000
#define TIMER_1_COMPARE_MATCH_B  0b10100000
#define TIMER_1_OVERFLOW         0b11000000
#define TIMER_1_CAPTURE_EVENT    0b11100000


/*ADC Channel PORTA */
#define ADC_CHANNEL_A0		0
#define ADC_CHANNEL_A1		1
#define ADC_CHANNEL_A2		2
#define ADC_CHANNEL_A3		3
#define ADC_CHANNEL_A4		4
#define ADC_CHANNEL_A5		5
#define ADC_CHANNEL_A6		6
#define ADC_CHANNEL_A7		7


#define ADC_AREF  			1
#define ADC_AVCC 			2
#define ADC_INTERNAL_2_56	3

#define ADC_TEN_BITS_MOOD   	 1
#define ADC_EIGHT_BITS_MOOD      2

#define	SINGLE_CONVERSION 		1
#define TURO_TRIGGER 			2

#define ADC_INTERRUPT_STATUS_ENABLE  		1
#define ADC_INTERRUPT_STATUS_DISABLE 		2

#define ADC_IDLE 	0
#define ADC_BUSY	1

#define  SINGLE_CHANNEL_ASYNCH 			0
#define  CHAIN_ASYNCH					1

#endif /* ADC_PRIVATE_H_ */
