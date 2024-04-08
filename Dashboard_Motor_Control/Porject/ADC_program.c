/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: ADC			  *******************/
/*************** Date: 10/3/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/


#include "BIT_Math.h"
#include "STD_TYPES.h"

#define F_CPU 8000000UL
#include <util/delay.h>

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_register.h"


/*Global pointer to carry the conversion result in the Asynchronous execution*/
static u16 * ADC_pu16AsynchConversionReading = NULL;

/*Global pointer to function to carry the notification function called by ISR*/
static void (*ADC_pvCallBackNotificationFunc)(void) = NULL;


/*Globally the Chain to used in ISR */
static u8* ADC_pu8ChainChannelArr = NULL;				/*Global variable to carry Chain Array */
static u8 ADC_u8ChainSize;								/*Global variable to carry Number of Channels*/
static u16* ADC_pu16ChainResultArr = NULL;				/*Global variable to carry chain results*/
static u8 ADC_u8ChainConversionIndex = 0;				/*Global variable to carry the current conversion index */

static u8 ADC_u8ISRSource;

/*State of ADC initial IDLE*/
u8 ADC_u8BusyState = ADC_IDLE;





void ADC_voidInit(void)
{
	/*Select the voltage reference*/
#if ADC_VOLT_REFRE == ADC_AREF
	CLR_BIT(ADMUX_REG , ADMUX_REFS0) ;
	CLR_BIT(ADMUX_REG , ADMUX_REFS1) ;

#elif ADC_VOLT_REFRE == ADC_AVCC
	SET_BIT(ADMUX_REG , ADMUX_REFS0) ;
	CLR_BIT(ADMUX_REG , ADMUX_REFS1) ;

#elif ADC_VOLT_REFRE == ADC_INTERNAL_2_56
	SET_BIT(ADMUX_REG , ADMUX_REFS0) ;
	SET_BIT(ADMUX_REG , ADMUX_REFS1) ;

#else
#error "Wrong ADC_VREF configuration"

#endif


	/*Selection the ADE Reading Adjustment*/
#if ADC_ADJUSTMENT_READING == ADC_TEN_BITS_MOOD
	CLR_BIT(ADMUX_REG , ADMUX_ADLAR) ;

#elif ADC_ADJUSTMENT_READING == ADC_EIGHT_BITS_MOOD
	SET_BIT(ADMUX_REG,ADMUX_ADLAR);

#else
#error "Wrong ADC_ADJUSTMENT configuration"

#endif


	/*Set the Pre_scaler BITS_MASKING*/
	ADCSRA_REG &= ADC_PRESCALERMASK;
	ADCSRA_REG |= ADC_PRESCALLER;


	/*Enable ADC Peripheral*/
	SET_BIT(ADCSRA_REG,ADCSRA_ADEN);



	/*	Setting Conversion Mood ADC  */
	/* Single Conversion Mood */
#if  ADC_CONVERSION_MOOD  ==  SINGLE_CONVERSION

	/* Clear the Auto trigger mode*/
	CLR_BIT(ADCSRA_REG,ADCSRA_ADATE);

	/*Disable interrupt*/
	CLR_BIT(ADCSRA_REG,ADCSRA_ADIE);


#elif ADC_CONVERSION_MOOD == TURO_TRIGGER

	/* Set the Auto trigger mode*/
	SET_BIT(ADCSRA_REG,ADCSRA_ADATE);

	/*Clear the Mux_bits in ADMUX register*/
	ADMUX_REG &= ADC_CHANNELMASK;
	/*Set the required channel into the Mux_bits*/
	ADMUX_REG |= SET_CHANNLE_AUTO_TRIGGER;

	/*Enable the interrupt must enable the GIE */
	SET_BIT(ADCSRA_REG,ADCSRA_ADIE);

	/*Set Trigger Options*/
	SFIOR_REG &=ADC_AUTO_TRIGGER_MASK;
	SFIOR_REG |=ADC_AUTO_TRIGGER;

	/*Start first Conversion*/
	SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

#else
#error "Wrong ADC_STATUS configuration"
#endif

}


u8 ADC_u16StartConversionSynch(u8 Copy_u8Channel , u16 *Copy_pu16Reading )
{
	u8	Local_u8ErrorStatu = STD_TYPES_OK;
	u32 Local_u32TimeoutCounter = 0 ;

	/*HINT:*****************
	 * is Safety for the Function is run and interrupt happen and call function again */
	if (ADC_u8BusyState == ADC_IDLE )
	{
		/*Make ADC is now Busy*/
		ADC_u8BusyState=ADC_BUSY;

		/*Clear the Mux_bits in ADMUX register*/
		ADMUX_REG &= ADC_CHANNELMASK;

		/*Set the required channel into the Mux_bits*/
		ADMUX_REG |= Copy_u8Channel;

		/*Start Conversion*/
		SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

		/*Polling (Busy waiting) until The conversion complete flag is set or Counter reaching Timeout_Value */
		while((GET_BIT(ADCSRA_REG,ADCSRA_ADIF) == 0) && (Local_u32TimeoutCounter != ADC_u32TIMEOUT ))
		{
			Local_u32TimeoutCounter++;
		}

		if (Local_u32TimeoutCounter == ADC_u32TIMEOUT)
		{
			/*Loop is broken because the timeout is reaching*/
			Local_u8ErrorStatu = STD_TIMEOUT_STATE;
		}

		else
		{
			/*Loop is broken because flag is risen*/

			/*Clear the conversion complete flag */
			SET_BIT(ADCSRA_REG,ADCSRA_ADIF);

			/*Selection the ADC Reading Adjustment*/
#if ADC_ADJUSTMENT_READING == ADC_TEN_BITS_MOOD
			*Copy_pu16Reading = ( ADCL_REG | (ADCH_REG << 8) ) ;

#elif ADC_ADJUSTMENT_READING == ADC_EIGHT_BITS_MOOD
			*Copy_pu16Reading = ADCH_REG;

#else
#error "Wrong ADC_ADJUSTMENT configuration"

#endif

			/*Make ADC State be IDLE because is finished*/
			ADC_u8BusyState = ADC_IDLE;
		}
	}

	else
	{
		/*Function is not finished  */
		Local_u8ErrorStatu = BUSY_FUNC;
	}


	/*Return error state*/
	return Local_u8ErrorStatu;
}



u8 ADC_u16StartConversionAsynch(u8 Copy_u8Channel , u16 *Copy_pu16Reading  , void (*Copy_PvNotificationFunction)(void)  )
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	if(ADC_u8BusyState == ADC_IDLE)
	{
		if ((Copy_pu16Reading == NULL) || (Copy_PvNotificationFunction == NULL))
		{
			Local_u8ErrorState =STD_TYPES_NOK;
		}
		else
		{
			/*Make ADC is now Busy*/
			ADC_u8BusyState = ADC_BUSY;

			/*Make ISR source single Channel Asynchronous*/
			ADC_u8ISRSource = SINGLE_CHANNEL_ASYNCH;

			/*Global variable to pointed in same addresses to used it in function ISR*/
			ADC_pu16AsynchConversionReading = Copy_pu16Reading;

			/*initialize The callback notification function globally*/
			ADC_pvCallBackNotificationFunc = Copy_PvNotificationFunction;

			/*Clear the Mux_bits in ADMUX register*/
			ADMUX_REG &= ADC_CHANNELMASK;

			/*Set the required channel into the Mux_bits*/
			ADMUX_REG |= Copy_u8Channel;

			/*Start Conversion*/
			SET_BIT(ADCSRA_REG,ADCSRA_ADSC);

			/*ADC Conversion Complete Interrupt Enable*/
			SET_BIT(ADCSRA_REG , ADCSRA_ADIE );

		}

	}

	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}

	return Local_u8ErrorState;
}



u8 ADC_u8StartChainAsynch(Chain_T *Copy_Chain)
{

	u8 Local_u8ErrorState=STD_TYPES_OK;

	/*Check NULL Pointer*/
	if (Copy_Chain == NULL)
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	else
	{
		if (ADC_u8BusyState == ADC_IDLE)
		{
			/*Make ADC Busy*/
			ADC_u8BusyState = ADC_BUSY;

			/*Make ISR source  : Chain Asynchronous*/
			ADC_u8ISRSource = CHAIN_ASYNCH ;


			/*Assign the ADC data globally*/
			/*Initialize chain Channel Array (Local -> global)*/
			ADC_pu8ChainChannelArr = Copy_Chain->Channel;
			/*Initialize Results Array*/
			ADC_pu16ChainResultArr = Copy_Chain->Result;
			/*Initialize chain Size*/
			ADC_u8ChainSize = Copy_Chain->Size;
			/*Initialize Notification Function*/
			ADC_pvCallBackNotificationFunc = Copy_Chain->NotificationFunction;
			/*Initialize current conversion index equal 0*/
			ADC_u8ChainConversionIndex = 0;

			/*Set required channel*/
			/*Clear the Mux_bits in ADMUX register*/
			ADMUX_REG &= ADC_CHANNELMASK;

			/*Set the required channel into the Mux_bits*/
			ADMUX_REG |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start Conversion*/
			SET_BIT(ADCSRA_REG , ADCSRA_ADSC);

			/*Enable Conversion complete interrupt*/
			SET_BIT(ADCSRA_REG , ADCSRA_ADIE);
		}

		else
		{
			Local_u8ErrorState = BUSY_FUNC;
		}
	}




	return Local_u8ErrorState;

}



void __vector_16 (void)  __attribute__((signal));
void __vector_16 (void)
{

	/*Function Single Conversion Asynchronous */
	if (ADC_u8ISRSource == SINGLE_CHANNEL_ASYNCH)
	{
		/*Read ADC Results*/
#if ADC_ADJUSTMENT_READING == ADC_TEN_BITS_MOOD
		*ADC_pu16AsynchConversionReading = ( ADCL_REG | (ADCH_REG << 8) ) ;

#elif ADC_ADJUSTMENT_READING == ADC_EIGHT_BITS_MOOD
		*ADC_pu16AsynchConversionReading = ADCH_REG;

#else
#error "Wrong ADC_ADJUSTMENT configuration"

#endif

		/*Make ADC State be IDLE because is finished*/
		ADC_u8BusyState = ADC_IDLE;

		/*Invoke the Callback notification Function*/
		ADC_pvCallBackNotificationFunc();

		/*Disable ADC Interrupt*/
		CLR_BIT(ADCSRA_REG , ADCSRA_ADIE);
	}



	else if(ADC_u8ISRSource == CHAIN_ASYNCH)
	{
		/*Read the Current Conversion*/
#if ADC_ADJUSTMENT_READING == ADC_TEN_BITS_MOOD
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ( ADCL_REG | (ADCH_REG << 8) ) ;

#elif ADC_ADJUSTMENT_READING == ADC_EIGHT_BITS_MOOD
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex] = ADCH_REG;

#else
#error "Wrong ADC_ADJUSTMENT configuration"

#endif

		/*Increment chain index*/
		ADC_u8ChainConversionIndex++;

		/*Check chain is finished or not*/
		if (ADC_u8ChainConversionIndex == ADC_u8ChainSize)
		{
			/*chain is finished*/
			/*Make ADC IDEL*/
			ADC_u8BusyState = ADC_IDLE;

			/*Invoke the Callback notification Function*/
			ADC_pvCallBackNotificationFunc();

			/*Disable ADC conversion Complete*/
			CLR_BIT(ADCSRA_REG , ADCSRA_ADIE);

		}
		else
		{
			/*chain is not finished */
			/*Set New required channel*/
			/*Clear the Mux_bits in ADMUX register*/
			ADMUX_REG &= ADC_CHANNELMASK;

			/*Set the required channel into the Mux_bits*/
			ADMUX_REG |= ADC_pu8ChainChannelArr[ADC_u8ChainConversionIndex];

			/*Start Next Conversion*/
			SET_BIT(ADCSRA_REG , ADCSRA_ADSC);
		}
	}
}





