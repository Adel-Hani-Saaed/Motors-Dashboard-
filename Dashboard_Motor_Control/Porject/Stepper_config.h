/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: Stepper_Motor	  *******************/
/*************** Date: 19/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#ifndef STEPPER_CONFIG_H_
#define STEPPER_CONFIG_H_

/* Description: LCD Control port configuration */
/* Range      : DIO_PORTA ~ DIO_PORTD */

#define STEPPER_PORT  		DIO_PORTA

/*Description: LCD RS pin */
/* Range     : DIO_PIN0 ~ DIO_PIN7 */

#define STEPPER_BLUE_PIN     DIO_PIN2
#define STEPPER_PINK_PIN     DIO_PIN3
#define STEPPER_YELLOW_PIN   DIO_PIN4
#define STEPPER_ORANGE_PIN   DIO_PIN5



#endif /* STEPPER_CONFIG_H_ */
