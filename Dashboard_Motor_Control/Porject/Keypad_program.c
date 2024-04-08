/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: Keypad		  *******************/
/*************** Date: 15/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/
#include "BIT_Math.h"
#include "STD_TYPES.h"

#define F_CPU 8000000UL
#include "avr/delay.h"

#include "DIO_interface.h"

#include "Keypad_config.h"
#include "Keypad_private.h"
#include "Keypad_interface.h"

void KPD_voidInit(void)
{
	/**********************************************************/
	/**********************************************************/
	/************** Row pins input and pull_up ****************/
	/**********************************************************/
	/**********************************************************/
	/*Define Row pins input */
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_R0,DIO_INPUT);
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_R1,DIO_INPUT);
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_R2,DIO_INPUT);
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_R3,DIO_INPUT);

	/*Configuration Row pins internal pull_up*/
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_R0,DIO_HIGH);
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_R1,DIO_HIGH);
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_R2,DIO_HIGH);
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_R3,DIO_HIGH);


	/**********************************************************/
	/**********************************************************/
	/************** Column pins output high *******************/
	/**********************************************************/
	/**********************************************************/
	/*Define Row pins input */
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_C0,DIO_OUTPUT);
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_C1,DIO_OUTPUT);
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_C2,DIO_OUTPUT);
	DIO_enumSetPinDirection(KPD_PORT,KPD_PIN_C3,DIO_OUTPUT);

	/*Configuration column pins set High*/
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_C0,DIO_HIGH);
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_C1,DIO_HIGH);
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_C2,DIO_HIGH);
	DIO_enumSetPinValue(KPD_PORT,KPD_PIN_C3,DIO_HIGH);
}

u8 KPD_u8GetPressedKey(void)
{
	/*Return the function if not pressed the keypad*/
	u8 Local_u8PressedKey=KPD_NO_PRESSES_KEY;

	/*Counters in the loops*/
	static u8 Local_u8ColumnIndex , Local_u8RowIndex , Local_u8PinState;

	/*Pattern Keypad of array 2 dimension*/
	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM]= {{ 7 , 8 , 9 ,'/'},
			{ 4 , 5 , 6 ,'*'},
			{ 1 , 2 , 3 ,'-'},
			{'%', 0 ,'=','+'}};
	;

	/*Array each column and row array Pins */
	static u8 Local_u8ColumnArr[COLUMN_NUM]={KPD_PIN_C0,KPD_PIN_C1,KPD_PIN_C2,KPD_PIN_C3};
	static u8 Local_u8RowArr[ROW_NUM]={KPD_PIN_R0,KPD_PIN_R1 ,KPD_PIN_R2 ,KPD_PIN_R3};

	/*Activate all columns high and low */
	for(Local_u8ColumnIndex = COLUMN_BEG ;Local_u8ColumnIndex < COLUMN_NUM ; Local_u8ColumnIndex++)
	{
		/*Activate Current Column*/
		DIO_enumSetPinValue(KPD_PORT, Local_u8ColumnArr[Local_u8ColumnIndex] , DIO_LOW);


		for(Local_u8RowIndex = ROW_BEG ; Local_u8RowIndex <ROW_NUM ; Local_u8RowIndex++ )
		{
			/*Read the current Row*/
			DIO_enumGetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIndex] ,&Local_u8PinState );

			/*Check if Switch is Pressed */
			if (DIO_LOW == Local_u8PinState)
			{
				Local_u8PressedKey = Local_u8KPDArr[Local_u8RowIndex][Local_u8ColumnIndex];

				/*Polling (busy waiting) until the Key is released*/
				/*stay here if the button is pressed, we could put delay 200 --> 250 ms instead of that*/
				while (DIO_LOW == Local_u8PinState)
				{
					DIO_enumGetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIndex] ,&Local_u8PinState );
				}

				return Local_u8PressedKey;
			}
		}
		/*deactivate Current Column*/
		DIO_enumSetPinValue(KPD_PORT, Local_u8ColumnArr[Local_u8ColumnIndex] , DIO_HIGH);
	}
	return Local_u8PressedKey;
}
