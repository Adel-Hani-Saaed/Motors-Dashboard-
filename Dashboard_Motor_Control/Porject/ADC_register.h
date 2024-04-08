/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: ADC			  *******************/
/*************** Date: 10/3/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_
/******************************************************************************************/
/********************************** Register File *****************************************/
/******************************************************************************************/
						/* Macros For ADC Control Registers */

#define ADMUX_REG	    	*((volatile u8 *)0x27)	    //ADC multiplexer selection register
#define ADMUX_REFS1			7                           //Reference selection bit1
#define ADMUX_REFS0			6							//Reference selection bit0
#define ADMUX_ADLAR         5							//ADC Left adjust result



#define ADCSRA_REG		    *((volatile u8 *)0x26)		//ADC control and status register A
#define ADCSRA_ADEN			7							//ADC enable
#define ADCSRA_ADSC			6							//Start conversion (Single conversion mode)
#define ADCSRA_ADATE		5							//Auto trigger enable ( Auto trigger mode )
#define ADCSRA_ADIF			4							//Interrupt flag (Auto clear when the ADC finished conversion will Set the Flag )
#define ADCSRA_ADIE			3							//Interrupt enable (PIE from ADC enable)
#define ADCSRA_ADPS2		2							//Pre_Scaler Bit2
#define ADCSRA_ADPS1		1							//Pre_Scaler Bit1
#define ADCSRA_ADPS0		0							//Pre_Scaler Bit0


#define ADC_REG				*((volatile u16 *)0x24)		//ADC RIGHT register (Right Adjust 10 Bits )
#define ADCH_REG			*((volatile u8 *)0x25)		//ADC high register	(Left Adjust 8 Bits)
#define ADCL_REG			*((volatile u8 *)0x24)		//ADC low register



#define SFIOR_REG			*((volatile u8 *)0x50) 		//ADC Special Function I/O Register
#define SFIOR_ADTS2			7                         	//Trigger Source bit2
#define SFIOR_ADTS1	     	6                         	//Trigger Source bit1
#define SFIOR_ADTS0		    5                         	//Trigger Source bit0


#endif /* ADC_REGISTER_H_ */
