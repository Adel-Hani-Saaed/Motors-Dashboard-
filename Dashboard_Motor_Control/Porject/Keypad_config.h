/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: Keypad		  *******************/
/*************** Date: 15/2/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/
#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_



//#define KPD_ARR_VAL		 {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'?','0','=','+'}};



/* Description: Keypad Port connection wire */
/* Range      :  1-DIO_PORTA
 * 				 2-DIO_PORTB
 *               3-DIO_PORTC
 *               4-DIO_PORTD  			*/

#define KPD_PORT  DIO_PORTC




/* Description: Configuration Pins connection wire  */
/* Range      :  1- DIO_PIN0
 * 				 2- DIO_PIN1
 *               3- DIO_PIN2
 *               4- DIO_PIN3
 *               5- DIO_PIN4
 *               6- DIO_PIN5
 *               7- DIO_PIN6
 *               8- DIO_PIN7                 */


#define KPD_PIN_R0    DIO_PIN0
#define KPD_PIN_R1    DIO_PIN1
#define KPD_PIN_R2    DIO_PIN2
#define KPD_PIN_R3    DIO_PIN3

#define KPD_PIN_C0    DIO_PIN4
#define KPD_PIN_C1    DIO_PIN5
#define KPD_PIN_C2    DIO_PIN6
#define KPD_PIN_C3    DIO_PIN7



#endif /* KEYPAD_CONFIG_H_ */
