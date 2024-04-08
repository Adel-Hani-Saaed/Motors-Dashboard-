/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: CLCD			  *******************/
/*************** Date: 12/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#include "STD_TYPES.h"
#include "BIT_Math.h"

#define F_CPU 8000000UL
#include "avr/delay.h"

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_pravite.h"
#include "CLCD_interface.h"
/******************************************************************************************/
/*********************************** Type Connection **************************************/
/**************** 8 Bits Mode************************************ 4 Bits Mode *************/
/******************************************************************************************
  -----------                   ----------           -----------                   ----------
 | ATmega32  |                 |   LCD    |         | ATmega32  |                 |   LCD    |
 |           |                 |          |         |           |                 |          |
 |        PA7|---------------->|D7        |         |        PA7|---------------->|D7        |
 |        PA6|---------------->|D6        |         |        PA6|---------------->|D6        |
 |        PA5|---------------->|D5        |         |        PA5|---------------->|D5        |
 |        PA4|---------------->|D4        |         |        PA4|---------------->|D4        |
 |        PA3|---------------->|D3        |         |        PA3|				  |D3        |
 |        PA2|---------------->|D2        |         |        PA2|				  |D2        |
 |        PA1|---------------->|D1        |         |        PA1|                 |D1        |
 |        PA0|---------------->|D0        |         |        PA0|                 |D0        |
 |           |                 |          |         |           |                 |          |
 |        PC2|---------------->|E         |         |        PC2|---------------->|E         |
 |        PC1|---------------->|RW (GND)  |         |        PC1|---------------->|RW (GND)  |
 |        PC0|---------------->|RS        |         |        PC0|---------------->|RS        |
  -----------                   ----------           -----------                   ----------
 */

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
#if CLCD_MODE == MODE_8_BIT

	/*Set RS pin to low for command*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_LOW);

	/*Set RW pin to low for write*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/*Set command to data pins*/
	DIO_enumSetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*Send enable pulse*/
	CLCD_voidSendPuls();


#elif CLCD_MODE == MODE_4_BIT
	/*Set RS pin to low for command*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_LOW);

	/*Set RW pin to low for write*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/*Send the most 4 bits of data to high nibbles*/
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN4 ,GET_BIT(Copy_u8Command,4));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN5 ,GET_BIT(Copy_u8Command,5));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN6 ,GET_BIT(Copy_u8Command,6));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN7 ,GET_BIT(Copy_u8Command,7));

	CLCD_voidSendPuls();

	/*Send the Least 4 bits of data to Low nibbles*/
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN4 ,GET_BIT(Copy_u8Command,0));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN5 ,GET_BIT(Copy_u8Command,1));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN6 ,GET_BIT(Copy_u8Command,2));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN7 ,GET_BIT(Copy_u8Command,3));

	CLCD_voidSendPuls();

#endif
}


void CLCD_voidSendData(u8 Copy_u8Data)
{

#if CLCD_MODE == MODE_8_BIT

	/*Set RS pin to low for command*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_HIGH);

	/*Set RW pin to low for write*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);

	/*Set command to data pins*/
	DIO_enumSetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*Send enable pulse*/
	CLCD_voidSendPuls();


#elif CLCD_MODE == MODE_4_BIT

	/*Set RS pin to low for command*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_HIGH);

	/*Set RW pin to low for write*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_LOW);


	/*Send the most 4 bits of data to high nibbles*/
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN4 ,GET_BIT(Copy_u8Data,4));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN5 ,GET_BIT(Copy_u8Data,5));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN6 ,GET_BIT(Copy_u8Data,6));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN7 ,GET_BIT(Copy_u8Data,7));


	CLCD_voidSendPuls();

	/*Send the Least 4 bits of data to Low nibbles*/
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN4 ,GET_BIT(Copy_u8Data,0));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN5 ,GET_BIT(Copy_u8Data,1));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN6 ,GET_BIT(Copy_u8Data,2));
	DIO_enumSetPinValue(CLCD_DATA_PORT ,DIO_PIN7 ,GET_BIT(Copy_u8Data,3));

	CLCD_voidSendPuls();

#endif
}




void CLCD_voidSendCharPosition(u8 Copy_u8Data, u8 Copy_u8Xposition , u8 Copy_u8Yposition)
{
	CLCD_voidGoToXY(Copy_u8Xposition,Copy_u8Yposition);
	CLCD_voidSendData(Copy_u8Data);
}





void CLCD_voidInit(void)
{
#if CLCD_MODE == MODE_8_BIT


	/*Set Direction Pins from LCD*/
	DIO_enumSetPortDirection(CLCD_DATA_PORT,DIO_PORT_OUTPUT);
	DIO_enumSetPinDirection(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_OUTPUT);


	/*Wait for more than 30 ms before any action (VDD rises to 4.5 v)*/
	_delay_ms(30);

	/*Function set command: 2 lines, 5*7 Font size*/
	CLCD_voidSendCommand(CLCD_FUNCSET_8BIT);

	/* wait more than 39 Ms*/
	_delay_ms(1);

	/*Display on off control: display enable, disable cursor, no blink cursor*/
	CLCD_voidSendCommand(CLCD_DISPON_CURSOFF);

	/* wait more than 39 Ms*/
	_delay_ms(1);

	/*Clear Display*/
	CLCD_voidSendCommand(CLCD_CLR);

	/* wait more than 1.53 Ms*/
	_delay_ms(2);


#elif CLCD_MODE == MODE_4_BIT

	/*Set Direction Pins from LCD*/
	DIO_enumSetPinDirection(CLCD_DATA_PORT,CLCD_DATA_PIN_ONE,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_DATA_PORT,CLCD_DATA_PIN_TWO,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_DATA_PORT,CLCD_DATA_PIN_THREE,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_DATA_PORT,CLCD_DATA_PIN_FOUR,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_OUTPUT);
	DIO_enumSetPinDirection(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_OUTPUT);

	/*Wait for more than 30 ms before any action (VDD rises to 4.5 v)*/
	_delay_ms(30);

	CLCD_voidSendCommand(0x33);
	CLCD_voidSendCommand(0x32);


	/*Function set command: 2 lines, 5*7 Font size*/
	CLCD_voidSendCommand(CLCD_FUNCSET_4BIT);

	/*Display on off control: display enable, disable cursor, no blink cursor*/
	CLCD_voidSendCommand(CLCD_DISPON_CURSOFF);

	/* wait more than 39 Ms*/
	_delay_ms(1);

	CLCD_voidSendCommand(CLCD_HOME);

	/*Clear Display*/
	CLCD_voidSendCommand(CLCD_CLR);

	/* wait more than 1.53 Ms*/
	_delay_ms(2);

	CLCD_voidSendCommand(CLCD_ENTRYMODE);

#else
#error ("You Chosed Wrong LCD Mode")

#endif
}


void CLCD_voidSendString(const char *Copy_pcString)
{
	u8 Local_u8Counter=0;

	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void CLCD_voidSendStringIndex_16(const char *Copy_pcString)
{
	u8 Local_u8Counter=0;

	while (Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
		if (Local_u8Counter == CLCD_COL_16 )
		{
			CLCD_voidGoToXY(CLCD_ROW_1,CLCD_COL_0);
			CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		}
	}
}



void CLCD_voidSendStringPosition(const char * Copy_puString , u8 Copy_u8Xposition , u8 Copy_u8Yposition)
{
	CLCD_voidGoToXY(Copy_u8Xposition,Copy_u8Yposition);
	CLCD_voidSendString(Copy_puString);
}



void CLCD_voidGoToXY(u8 Copy_u8XPosition , u8 Copy_u8YPosition )
{
	u8 Local_u8Address;

	if (Copy_u8XPosition == CLCD_ROW_0)
	{
		/*Location is at first line*/
		Local_u8Address = Copy_u8YPosition;
	}

	else if( Copy_u8XPosition == CLCD_ROW_1)
	{
		/*Location is at Second line*/
		Local_u8Address = Copy_u8YPosition + CLCD_SET_DDRAM_ROW1;
	}
	/*Set bit number 7 (10000000) for set DDRAM Address Command than send the command  */
	CLCD_voidSendCommand(Local_u8Address + CLCD_SET_DDRAM_COMMAND);
}



void CLCD_voidSpecialCharacter(u8* Copy_pu8Pattern ,u8 Copy_u8PatternNumber ,u8 Copy_u8XPosition,u8 Copy_u8YPosition)
{
	u8 Local_u8CGRAMAddress=0;
	u8 Local_u8Iterator;

	/*Calculate the CGRAM Address whose each block is 8 bytes*/
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;

	/*Send command i need write in  CGRAM address command to LCD , with set bit 6 , clearing bit 7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress + CLCD_SET_CGRAM_ADDRESS);

	/*Write the pattern into CGRAM bit by bit in block 8bits */
	for (Local_u8Iterator=0 ; Local_u8Iterator <8 ; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}

	/*Go back to the DDRAM to Display the Pattern*/
	CLCD_voidGoToXY(Copy_u8XPosition,Copy_u8YPosition);

	/*display the pattern written in the CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}


void CLCD_voidPrintINTNumber(u64 Copy_u16Number)
{

	u32 arr[10]={0}, Index_u8Array=10;

	if (Copy_u16Number == 0){ CLCD_voidSendData('0'); }

	else{
		while (Copy_u16Number != 0)
		{
			arr[Index_u8Array-1]=(Copy_u16Number%10)+'0';
			Copy_u16Number=Copy_u16Number/10;
			Index_u8Array--;
		}
		for (; Index_u8Array<=9 ; Index_u8Array++ )
		{
			CLCD_voidSendData(arr[Index_u8Array]);
		}
	}
}

void CLCD_voidSendINTNumberPosition(u32 Copy_u16Number , u8 Copy_u8Xposition , u8 Copy_u8Yposition)
{
	CLCD_voidGoToXY(Copy_u8Xposition,Copy_u8Yposition);
	CLCD_voidPrintINTNumber(Copy_u16Number);
}




void CLCD_voidClearLCD(void)
{
	CLCD_voidSendCommand(CLCD_CLR);

	//wait more than 1.53 ms
	_delay_ms(10);

}

void CLCD_voidClearLCDPosition(u8 Copy_u8XPostion,u8 Copy_u8YPostion)
{
	CLCD_voidGoToXY(Copy_u8XPostion,Copy_u8YPostion);
	CLCD_voidSendData(' ');
}




void CLCD_voidCursorOff(void)
{
	CLCD_voidSendCommand(CLCD_DISPON_CURSOFF);
	_delay_ms(2);
}

void CLCD_voidCursorOn(void)
{
	CLCD_voidSendCommand(CLCD_DISPON_CURSON);
	_delay_ms(2);
}


void CLCD_voidCursorBlink(void)
{
	CLCD_voidSendCommand(CLCD_DISPON_CURSBLINK);
	_delay_ms(2);
}


void CLCD_voidSendPuls(void)
{
	/*FallingEdge*/
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_HIGH);
	_delay_ms(2);
	DIO_enumSetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_LOW);
	_delay_ms(2);
}




