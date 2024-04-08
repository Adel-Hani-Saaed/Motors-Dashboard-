/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: Stepper_Motor	  *******************/
/*************** Date: 19/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#include "BIT_Math.h"
#include "STD_TYPES.h"
#define F_CPU 8000000UL
#include "util/delay.h"

#include "DIO_interface.h"
#include "Stepper_config.h"
#include "Stepper_interface.h"


void STEPPER_voidInit( void )
{
	/* Set pin direction output */
	DIO_enumSetPinDirection(STEPPER_PORT,STEPPER_BLUE_PIN,STEPPER_PIN_OUTPUT);
	DIO_enumSetPinDirection(STEPPER_PORT,STEPPER_PINK_PIN,STEPPER_PIN_OUTPUT);
	DIO_enumSetPinDirection(STEPPER_PORT,STEPPER_ORANGE_PIN,STEPPER_PIN_OUTPUT);
	DIO_enumSetPinDirection(STEPPER_PORT,STEPPER_YELLOW_PIN,STEPPER_PIN_OUTPUT);

	/* Set pin value Low (Stepper motor Turn off) */
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_BLUE_PIN,STEPPER_PIN_LOW);
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_PINK_PIN,STEPPER_PIN_LOW);
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_ORANGE_PIN,STEPPER_PIN_LOW);
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_YELLOW_PIN,STEPPER_PIN_LOW);
}


void STEPPER_voidTurnOn  ( u8 Copy_u8StepType , u8 Copy_u8Direction , u8 Copy_u8Speed , u16 Copy_u16Degree )
{
	u32 Local_u32Iterator = 0 ;

	if( Copy_u8StepType == STEPPER_FULL_STEP )
	{


		if( Copy_u8Direction == STEPPER_ANTI_CLOCK_WISE )
		{

			for( Local_u32Iterator = 0 ; Local_u32Iterator < ( ( (u32)Copy_u16Degree * 256 ) / 45 ) / 4 ; Local_u32Iterator++  )
			{
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );
			}

		}


		else if( Copy_u8Direction == STEPPER_CLOCK_WISE )
		{

			for( Local_u32Iterator = 0 ; Local_u32Iterator < ( ( (u32)Copy_u16Degree * 256 ) / 45 ) / 4 ; Local_u32Iterator++  )
			{

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );
			}
		}
	}



	else if( Copy_u8StepType == STEPPER_HALF_STEP )
	{

		if( Copy_u8Direction == STEPPER_ANTI_CLOCK_WISE )
		{

			for( Local_u32Iterator = 0 ; Local_u32Iterator < ( ( (u32)Copy_u16Degree * 512 ) / 45 ) / 8 ; Local_u32Iterator++  )
			{

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );
			}

		}


		else if( Copy_u8Direction == STEPPER_CLOCK_WISE )
		{


			for( Local_u32Iterator = 0 ; Local_u32Iterator < ( ( (u32)Copy_u16Degree * 512 ) / 45 ) / 8 ; Local_u32Iterator++  )
			{
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_HIGH );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );

				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_BLUE_PIN   , DIO_HIGH );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_PINK_PIN   , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_YELLOW_PIN , DIO_LOW  );
				DIO_enumSetPinValue( STEPPER_PORT , STEPPER_ORANGE_PIN , DIO_LOW  );
				_delay_ms( Copy_u8Speed );
			}
		}
	}
}


void STEPPER_voidTurnOff ( void )
{
	/* Set pin value Low (Stepper motor Turn off) */
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_BLUE_PIN,STEPPER_PIN_LOW);
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_PINK_PIN,STEPPER_PIN_LOW);
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_ORANGE_PIN,STEPPER_PIN_LOW);
	DIO_enumSetPinValue(STEPPER_PORT,STEPPER_YELLOW_PIN,STEPPER_PIN_LOW);
}
