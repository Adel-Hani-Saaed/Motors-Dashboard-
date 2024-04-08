/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: Timer0		  *******************/
/*************** Date: 27/3/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#include "BIT_Math.h"
#include "STD_TYPES.h"

#include "Timer0_interface.h"
#include "Timer0_private.h"  				//Hint: must include the file private before file configuration
#include "Timer0_config.h"
#include "Timer0_register.h"


//static void (*Timer0_pvCallBackFuncCTCMode)(void) = NULL;
//static void (*Timer0_pvCallBackFuncOverFlowMode)(void) = NULL;


void TIMER0_voidInit()
{
	/*Set Configurable Modes*/
#if TIMER0_WAVEFORM_GENERATION_MODE == TIMER_NORMAL_MODE

	/*Initialize Waveform Generation Mode as Normal Mode*/
	CLR_BIT(TCCR0_REG, TCCR0_WGM00);
	CLR_BIT(TCCR0_REG, TCCR0_WGM01);

	/*Set value PreLoad*/
	TCNT0_REG = TIMER0_PRELOAD_VAL;

	/*Timer0 Overflow Interrupt Enable*/
#if TIMER0_OVERFLOW_INTERRUPT == DISABLE

	CLR_BIT(TIMSK_REG , TIMSK_TOIE0);

#elif TIMER0_OVERFLOW_INTERRUPT == ENABLE
	SET_BIT(TIMSK_REG , TIMSK_TOIE0);

#else
#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
#endif


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_CTC_MODE

	/*Initialize Waveform Generation Mode as CTC Mode*/
	CLR_BIT(TCCR0_REG , TCCR0_WGM00) ;
	SET_BIT(TCCR0_REG , TCCR0_WGM01) ;

	/*Set the Required CTC Value*/
	OCR0_REG = TIMER0_CTC_VAL ;

	/*Timer0 Compare Match Interrupt Enable*/
#if TIMER0_CTC_INTERRUPT == DISABLE
	CLR_BIT(TIMSK_REG , TIMSK_OCIE0) ;

#elif TIMER0_CTC_INTERRUPT == ENABLE
	SET_BIT(TIMSK_REG , TIMSK_OCIE0) ;

#else
#error "Wrong TIMER0_OVERFLOW_INTERRUPT Config"
#endif


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_FAST_PWM_MODE

	/*Initialize Waveform Generation Mode as Fast PWM Mode*/
	SET_BIT(TCCR0_REG , TCCR0_WGM00) ;
	SET_BIT(TCCR0_REG , TCCR0_WGM01) ;

	/*Set CTC Fast PWM MODE*/
#if TIMER0_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR0_REG , TCCR0_COM00) ;
	CLR_BIT(TCCR0_REG , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
	CLR_BIT(TCCR0_REG , TCCR0_COM00) ;
	SET_BIT(TCCR0_REG , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
	SET_BIT(TCCR0_REG , TCCR0_COM00) ;
	SET_BIT(TCCR0_REG , TCCR0_COM01) ;
#else
#error "Wrong TIMER0_CTC_PWM_MODE Config"
#endif

	/*Set the Required CTC Value*/
	OCR0_REG = TIMER0_CTC_VAL;

#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER_PWM_PHASE_CORRECT_MODE

	/*Initialize Waveform Generation Mode as Phase Correct PWM Mode*/
	SET_BIT(TCCR0_REG , TCCR0_WGM00) ;
	CLR_BIT(TCCR0_REG , TCCR0_WGM01) ;

	/*Set CTC Fast PWM MODE*/
#if TIMER0_CTC_PWM_MODE == TIMER_OC_DISCONNECTED
	CLR_BIT(TCCR0_REG , TCCR0_COM00) ;
	CLR_BIT(TCCR0_REG , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_COUNTING_UP_SET_ON_CTC_COUNTING_DWON
	CLR_BIT(TCCR0_REG , TCCR0_COM00) ;
	SET_BIT(TCCR0_REG , TCCR0_COM01) ;
#elif TIMER0_CTC_PWM_MODE == TIMER_CLR_ON_CTC_COUNTING_DWON_SET_ON_CTC_COUNTING_UP
	SET_BIT(TCCR0_REG , TCCR0_COM00) ;
	SET_BIT(TCCR0_REG , TCCR0_COM01) ;
#else
#error "Wrong TIMER0_CTC_PWM_MODE Config"
#endif

	/*Set the Required CTC Value*/
	OCR0_REG = TIMER0_CTC_VAL;


#else
	#error "Wrong TIMER0_WAVEFORM_GENERATION_MODE Config"

#endif

	/*Set the Required Pre_scaler*/
	TCCR0_REG &= TIMER_PRESCALER_MASK ;
	TCCR0_REG |= TIMER0_PRESCALER ;
}


void TIMER0_voidSetPreloadValue (u8 Copy_u8PreloadValue)
{
	TCNT0_REG = Copy_u8PreloadValue;
}

void TIMER0_voidSetCompMatchValue(u8 Copy_u8CTCValue)
{

	OCR0_REG = Copy_u8CTCValue;

}

//
//u8 TIMER0_u8SetCallBackCTCMode(void (*Copy_pvCallBackFunc)(void))
//{
//	u8 Local_u8ErrorState = STD_TYPES_OK;
//
//	if (Copy_pvCallBackFunc != NULL)
//	{
//		Timer0_pvCallBackFuncCTCMode = Copy_pvCallBackFunc;
//	}
//	else
//	{
//		Local_u8ErrorState = STD_TYPES_NOK;
//
//	}
//
//	return Local_u8ErrorState;
//}
//
//
///*TIMER0 CTC Mode ISR*/
//void __vector_10 (void) __attribute__((signal));
//void __vector_10 (void)
//{
//	if (Timer0_pvCallBackFuncCTCMode != NULL)
//	{
//		Timer0_pvCallBackFuncCTCMode();
//	}
//}
//
//
//
//u8 TIMER0_u8SetCallBackOverFlowMode(void (*Copy_pvCallBackFunc)(void))
//{
//	u8 Local_u8ErrorState = STD_TYPES_OK;
//
//	if (Copy_pvCallBackFunc != NULL)
//	{
//		Timer0_pvCallBackFuncOverFlowMode = Copy_pvCallBackFunc;
//	}
//	else
//	{
//		Local_u8ErrorState = STD_TYPES_NOK;
//
//	}
//
//	return Local_u8ErrorState;
//}
//
///*TIMER0 Normal Mode ISR*/
//void __vector_11 (void) __attribute__((signal));
//void __vector_11 (void)
//{
//	if (Timer0_pvCallBackFuncOverFlowMode != NULL)
//	{
//		Timer0_pvCallBackFuncOverFlowMode();
//	}
//}
