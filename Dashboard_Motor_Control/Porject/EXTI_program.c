/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: MCAL		  *******************/
/*************** SWC: EXTI			  *******************/
/*************** Date: 27/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#include "BIT_Math.h"
#include "STD_TYPES.h"


#include "EXTI_config.h"
#include "EXTI_private.h"
#include "EXTI_register.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"


/* Global Pointers to function to hold INT0 , INT1 and INT2 ISR address */
// return type    (pinter to function)    (input)   = Null (if not have the address function)
void (* EXTI_pvINT0PointerToFunc)(void) = NULL;
void (* EXTI_pvINT1PointerToFunc)(void) = NULL;
void (* EXTI_pvINT2PointerToFunc)(void) = NULL;


void EXTI_voidINT0Init (void)
{

#if EXTI_INT0_SENSE == EXTI_u8_LOW_LEVEL
	CLR_BIT(MCUCR_REG,MCUCR_ISC01);
	CLR_BIT(MCUCR_REG,MCUCR_ISC00);

#elif EXTI_INT0_SENSE == EXTI_u8_ANY_LOGICAL_CHANGE
	CLR_BIT(MCUCR_REG,MCUCR_ISC01);
	SET_BIT(MCUCR_REG,MCUCR_ISC00);

#elif EXTI_INT0_SENSE == EXTI_u8_FALLING_EDGE
	SET_BIT(MCUCR_REG,MCUCR_ISC01);
	CLR_BIT(MCUCR_REG,MCUCR_ISC00);

#elif EXTI_INT0_SENSE == EXTI_u8_RISING_EDGE
	SET_BIT(MCUCR_REG,MCUCR_ISC01);
	SET_BIT(MCUCR_REG,MCUCR_ISC00);

#else
#error"Wrong EXTI_INT0_SENSE configuration is not option"
#endif

#if EXTI_INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR_REG,GICR_INT0);

#elif EXTI_INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR_REG,GICR_INT0);
#else
#error"Wrong EXTI_INT0_INITIAL_STATE configuration is not option"
#endif
}



void EXTI_voidINT1Init (void)
{
#if EXTI_INT1_SENSE == EXTI_u8_LOW_LEVEL
	CLR_BIT(MCUCR_REG,MCUCR_ISC11);
	CLR_BIT(MCUCR_REG,MCUCR_ISC10);

#elif EXTI_INT1_SENSE == EXTI_u8_ANY_LOGICAL_CHANGE
	CLR_BIT(MCUCR_REG,MCUCR_ISC11);
	SET_BIT(MCUCR_REG,MCUCR_ISC10);

#elif EXTI_INT1_SENSE == EXTI_u8_FALLING_EDGE
	SET_BIT(MCUCR_REG,MCUCR_ISC11);
	CLR_BIT(MCUCR_REG,MCUCR_ISC10);

#elif EXTI_INT1_SENSE == EXTI_u8_RISING_EDGE
	SET_BIT(MCUCR_REG,MCUCR_ISC11);
	SET_BIT(MCUCR_REG,MCUCR_ISC10);

#else
#error"Wrong EXTI_INT1_SENSE configuration is not option"
#endif

#if EXTI_INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR_REG,GICR_INT1);

#elif EXTI_INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR_REG,GICR_INT1);
#else
#error"Wrong EXTI_INT1_INITIAL_STATE configuration is not option"
#endif
}



void EXTI_voidINT2Init (void)
{

#if EXTI_INT2_SENSE == EXTI_u8_FALLING_EDGE
	CLR_BIT(MCUCSR_REG,MCUCSR_ISC2);

#elif EXTI_INT2_SENSE == EXTI_u8_RISING_EDGE
	SET_BIT(MCUCSR_REG,MCUCSR_ISC2);

#else
#error"Wrong EXTI_INT2_SENSE configuration is not option"
#endif

#if EXTI_INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR_REG,GICR_INT2);

#elif EXTI_INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR_REG,GICR_INT2);
#else
#error"Wrong EXTI_INT2_INITIAL_STATE configuration is not option"
#endif
}




u8 EXTI_u8ExtIEnable(u8 Copy_u8IntNum, u8 Copy_u8IntEdgeSrc)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;

	switch(Copy_u8IntNum)
	{
	case EXTI_u8_INT0 :
		switch(Copy_u8IntEdgeSrc)
		{
		case EXTI_u8_FALLING_EDGE:
			SET_BIT(MCUCR_REG,MCUCR_ISC01);
			CLR_BIT(MCUCR_REG,MCUCR_ISC00);
			SET_BIT(GICR_REG,GICR_INT0);

			break;
		case EXTI_u8_RISING_EDGE:
			SET_BIT(MCUCR_REG,MCUCR_ISC01);
			SET_BIT(MCUCR_REG,MCUCR_ISC00);
			SET_BIT(GICR_REG,GICR_INT0);

			break;
		case EXTI_u8_ANY_LOGICAL_CHANGE:
			CLR_BIT(MCUCR_REG,MCUCR_ISC01);
			SET_BIT(MCUCR_REG,MCUCR_ISC00);
			SET_BIT(GICR_REG,GICR_INT0);

			break;
		case EXTI_u8_LOW_LEVEL:
			CLR_BIT(MCUCR_REG,MCUCR_ISC01);
			CLR_BIT(MCUCR_REG,MCUCR_ISC00);
			SET_BIT(GICR_REG,GICR_INT0);

			break;
		default : Local_u8ErrorState = STD_TYPES_NOK;
		}
		break;

		case EXTI_u8_INT1 :
			switch(Copy_u8IntEdgeSrc)
			{
			case EXTI_u8_FALLING_EDGE:
				SET_BIT(MCUCR_REG,MCUCR_ISC11);
				CLR_BIT(MCUCR_REG,MCUCR_ISC10);
				SET_BIT(GICR_REG,GICR_INT1);
				break;
			case EXTI_u8_RISING_EDGE:
				SET_BIT(MCUCR_REG,MCUCR_ISC11);
				SET_BIT(MCUCR_REG,MCUCR_ISC10);
				SET_BIT(GICR_REG,GICR_INT1);
				break;
			case EXTI_u8_ANY_LOGICAL_CHANGE:
				CLR_BIT(MCUCR_REG,MCUCR_ISC11);
				SET_BIT(MCUCR_REG,MCUCR_ISC10);
				SET_BIT(GICR_REG,GICR_INT1);
				break;
			case EXTI_u8_LOW_LEVEL:
				CLR_BIT(MCUCR_REG,MCUCR_ISC11);
				CLR_BIT(MCUCR_REG,MCUCR_ISC10);
				SET_BIT(GICR_REG,GICR_INT1);
				break;
			default : Local_u8ErrorState = STD_TYPES_NOK;
			}
			break;

			case EXTI_u8_INT2 :
				switch(Copy_u8IntEdgeSrc)
				{
				case EXTI_u8_FALLING_EDGE:
					CLR_BIT(MCUCSR_REG,MCUCSR_ISC2);
					SET_BIT(GICR_REG,GICR_INT2);
					break;
				case EXTI_u8_RISING_EDGE:
					SET_BIT(MCUCSR_REG,MCUCSR_ISC2);
					SET_BIT(GICR_REG,GICR_INT2);
					break;
				default : Local_u8ErrorState = STD_TYPES_NOK;
				}
				break;
				default : Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


u8 EXTI_u8ExtIDisable(u8 Copy_u8IntNum)

{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8IntNum)
	{
	case EXTI_u8_INT0 :
		CLR_BIT(GICR_REG,GICR_INT0);
		break;
	case EXTI_u8_INT1 :
		CLR_BIT(GICR_REG,GICR_INT1);
		break;
	case EXTI_u8_INT2 :
		CLR_BIT(GICR_REG,GICR_INT2);
		break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}





/*must be pass the Address the function callback (&Name_Func) or (Name_func) because name the function is address the function */
u8 EXTI_u8ExtISetCallBackINT0 (void (*Copy_pvInt0Func)(void))
{
	u8 Local_u8ErrorState=STD_TYPES_OK;

	if (Copy_pvInt0Func != NULL)
	{
		EXTI_pvINT0PointerToFunc = Copy_pvInt0Func;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;

}


/*must be pass the Address the function callback (&Name_Func) or (Name_func) because name the function is address the function */
u8 EXTI_u8ExtISetCallBackINT1 (void (*Copy_pvInt1Func)(void))
{
	u8 Local_u8ErrorState=STD_TYPES_OK;

	if (Copy_pvInt1Func != NULL)
	{
		EXTI_pvINT1PointerToFunc = Copy_pvInt1Func;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}



/*must be pass the Address the function callback (&Name_Func) or (Name_func) because name the function is address the function */
u8 EXTI_u8ExtISetCallBackINT2 (void (*Copy_pvInt2Func)(void))
{
	u8 Local_u8ErrorState=STD_TYPES_OK;

	if (Copy_pvInt2Func != NULL)
	{
		EXTI_pvINT2PointerToFunc = Copy_pvInt2Func;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}



/* ISR Of INT0 , INT1 and INT2 to calling the function Callback in main */

void __vector_1 (void)  __attribute__((signal));
void __vector_1 (void)
{
	if (EXTI_pvINT0PointerToFunc != NULL)
	{
		/*calling the function (Pointer to function)*/
		EXTI_pvINT0PointerToFunc();
	}
	else
	{
		/*Do nothing*/
	}
}


void __vector_2 (void)  __attribute__((signal));
void __vector_2 (void)
{
	if (EXTI_pvINT1PointerToFunc != NULL)
	{
		/*calling the function (Pointer to function)*/
		EXTI_pvINT1PointerToFunc();
	}
	else
	{
		/*Do nothing*/
	}

}


void __vector_3 (void)  __attribute__((signal));
void __vector_3 (void)
{
	/*check the Pointer */
	if (EXTI_pvINT2PointerToFunc != NULL)
	{
		/*calling the function (Pointer to function)*/
		EXTI_pvINT2PointerToFunc();
	}
	else
	{
		/*Do nothing*/
	}
}

