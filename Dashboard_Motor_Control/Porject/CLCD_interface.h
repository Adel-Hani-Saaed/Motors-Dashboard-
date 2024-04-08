/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: CLCD			  *******************/
/*************** Date: 12/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

/**********************************************************/
/******************* Public Definitions *******************/
/**********************************************************/
/*Comment!: LCD control commands*/

#define CLCD_CLR           		0x01          // replace all characters with ASCII 'space'
#define CLCD_HOME          		0x02          // return cursor to first position on first line
#define CLCD_ENTRYMODE     		0x06          // shift cursor from left to right on read/write
#define CLCD_DISPOFF       		0x08          // turn display off
#define CLCD_FUNCRESET     		0x30          // reset the LCD
#define CLCD_FUNCSET_8BIT  		0x38          // 8-bit data, 2-line display, 5 x 7 font
#define CLCD_FUNCSET_4BIT  		0x28		  // 4 bits mode initialization
#define CLCD_SETCURSOR     		0x80          // set cursor position
#define CLCD_DISPON_CURSBLINK	0x0F 		  // display on , cursor blinking
#define CLCD_DISPON_CURSOFF		0x0C 		  // display on ,cursor off
#define CLCD_DISPON_CURSON 		0x0E          // display on, cursor off, don't blink character

/*Comment!: LCD control commands for fun*/
#define CLCD_SHIFTENTIRE_RIGHT          	0x1c          // shift entire display right
#define CLCD_SHIFTENTIRE_LEFT          		0x18          // shift entire display Left
#define CLCD_JUMPSECONDLINE_P0				0xc0		  // Jump to second line Position 0
#define CLCD_JUMPSECONDLINE_P1				0xc1		  // Jump to second line Position 1
#define CLCD_JUMPSECONDLINE_P2				0xc2		  // Jump to second line Position 2
#define CLCD_JUMPSECONDLINE_P3				0xc3		  // Jump to second line Position 3
#define CLCD_JUMPSECONDLINE_P4				0xc4		  // Jump to second line Position 4
#define CLCD_JUMPSECONDLINE_P5				0xc5		  // Jump to second line Position 5
#define CLCD_JUMPSECONDLINE_P6				0xc6		  // Jump to second line Position 6
#define CLCD_JUMPSECONDLINE_P7				0xc7		  // Jump to second line Position 7

#define CLCD_ROW_0   0
#define CLCD_ROW_1   1

#define CLCD_COL_0   0
#define CLCD_COL_1   1
#define CLCD_COL_2   2
#define CLCD_COL_3   3
#define CLCD_COL_4   4
#define CLCD_COL_5   5
#define CLCD_COL_6   6
#define CLCD_COL_7   7
#define CLCD_COL_8   8
#define CLCD_COL_9   9
#define CLCD_COL_10  10
#define CLCD_COL_11  11
#define CLCD_COL_12  12
#define CLCD_COL_13  13
#define CLCD_COL_14  14
#define CLCD_COL_15  15
#define CLCD_COL_16  16


/***************************************************************************************/
/* Description! Apply Send Command for LCD 					                           */
/* Input      ! Command                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidSendCommand(u8 Copy_u8Command);


/***************************************************************************************/
/* Description! Apply Send Data for LCD 					                           */
/* Input      ! Data                                                            	   */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendCharPosition(u8 Copy_u8Data, u8 Copy_u8Xposition , u8 Copy_u8Yposition);


/***************************************************************************************/
/* Description! Apply initialization sequence for LCD module                           */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidInit(void);


/***************************************************************************************/
/* Description! Function Send String in LCD 				                           */
/* Input      ! String (array of characters)                                                                */
/* Output     ! Nothing     														   */
/* Hint : when u need pass the String ASCII must be char only not (unsigned or signed )*/
/***************************************************************************************/
void CLCD_voidSendString(const char *Copy_pcString);
void CLCD_voidSendStringIndex_16(const char *Copy_pcString);
void CLCD_voidSendStringPosition(const char * Copy_puString , u8 Copy_u8Xposition , u8 Copy_u8Yposition);

/***************************************************************************************/
/* Description! Function go to the position in LCD 				                       */
/* Input      ! Position x and y                                                                */
/* Output     ! Nothing     														   */
/***************************************************************************************/
void CLCD_voidGoToXY(u8 Copy_u8XPosition , u8 Copy_u8YPosition );


/***************************************************************************************/
/* Description! Function Write Special Character in LCD (CGRAM)	                       */
/* Input      ! Pattern the character                                                                */
/* Output     ! Nothing     														   */
/***************************************************************************************/
void CLCD_voidSpecialCharacter(u8* Copy_pu8Pattern ,u8 Copy_u8PatternNumber ,u8 Copy_u8XPosition,u8 Copy_u8YPosition);


/***************************************************************************************/
/* Description! Function Write the integer numbers in LCD 		                       */
/* Input      ! integer numbers                                                                */
/* Output     ! Nothing     														   */
/***************************************************************************************/
void CLCD_voidPrintINTNumber(u64 Copy_u16Number);
void CLCD_voidSendINTNumberPosition(u32 Copy_u16Number , u8 Copy_u8Xposition , u8 Copy_u8Yposition);


/***************************************************************************************/
/* Description! Function to send High to Low enable pulse to LCD                       */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidSendPuls(void);


/***************************************************************************************/
/* Description! LCD Clear Screen Function.	                     					   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidCursorOff(void);

/***************************************************************************************/
/* Description! LCD Cursor ON Function.		                     					   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidCursorOn(void);

/***************************************************************************************/
/* Description!  LCD Cursor Blink Function.		                  					   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidCursorBlink(void);

/***************************************************************************************/
/* Description! LCD Clear Screen Function.	                     					   */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void CLCD_voidClearLCD(void);
void CLCD_voidClearLCDPosition(u8 Copy_u8XPostion,u8 Copy_u8YPostion);

#endif /* CLCD_INTERFACE_H_ */
