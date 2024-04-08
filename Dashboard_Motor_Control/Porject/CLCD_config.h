/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: CLCD			  *******************/
/*************** Date: 12/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/* Description: LCD Mode Configuration */
/* Range      : 1- MODE_8_BIT
 * 				2- MODE_4_BIT  */
#define CLCD_MODE  MODE_4_BIT

/************************************************************************/
/********************* PORT/PINs configurations for LCD *****************/
/************************************************************************/
/* Description: LCD DATA port configuration */
/* Range      : DIO_u8PORTA ~ DIO_u8PORTD */

#define CLCD_DATA_PORT				DIO_PORTB

/*********************************************************
 * Description: LCD DATA PINS in 4 bits mode Configuration
 ********************************************************/
#define CLCD_DATA_PIN_ONE   	   	DIO_PIN4
#define CLCD_DATA_PIN_TWO   	    DIO_PIN5
#define CLCD_DATA_PIN_THREE         DIO_PIN6
#define CLCD_DATA_PIN_FOUR          DIO_PIN7

/* Description: LCD Control port configuration */
/* Range      : DIO_PORTA ~ DIO_PORTD */
#define CLCD_CTRL_PORT				DIO_PORTB

/*Description: LCD RS pin */
/* Range     : DIO_PIN0 ~ DIO_PIN7 */
#define CLCD_RS_PIN					DIO_PIN0

/*Description: LCD RW pin (Connection with GND because we always Write in LCD )*/
/* Range     : DIO_PIN0 ~ DIO_PIN7 */
#define CLCD_RW_PIN					DIO_PIN1

/*Description: LCD E pin */
/* Range     : DIO_PIN0 ~ DIO_PIN7 */
#define CLCD_E_PIN					DIO_PIN2

#endif /* CLCD_CONFIG_H_ */
