/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL 		  *******************/
/*************** DCMOTORC: DC_Motor		  *******************/
/*************** Date: 18/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#ifndef DC_MOTOR_INTERFACE_H_
#define DC_MOTOR_INTERFACE_H_

 /*State direction*/
#define DCMOTOR_CW		0
#define DCMOTOR_CCW		1
#define DCMOTOR_STOP	2

//  DCMOTOR Port Macros
#define DCMOTOR_PORTA    0
#define DCMOTOR_PORTB    1
#define DCMOTOR_PORTC    2
#define DCMOTOR_PORTD    3

//  DCMOTOR Pin Macros
#define DCMOTOR_PIN0     0
#define DCMOTOR_PIN1     1
#define DCMOTOR_PIN2     2
#define DCMOTOR_PIN3     3
#define DCMOTOR_PIN4     4
#define DCMOTOR_PIN5     5
#define DCMOTOR_PIN6     6
#define DCMOTOR_PIN7     7

//  DCMOTOR direction
#define DCMOTOR_PIN_OUTPUT   1
#define DCMOTOR_PIN_INPUT    0

//  DCMOTOR State
#define DCMOTOR_PIN_HIGH   1
#define DCMOTOR_PIN_LOW	   0


typedef struct
{
	u8 DcMotorPort ;
	u8 DcMotorPinA ;
	u8 DcMotorPinB ;
} DCMOTOR_CONFIG ;



void DCMOTOR_voidInit(DCMOTOR_CONFIG *DC_MOTOR_structConfig);

u8 DCMOTOR_uint8ControlDirection (DCMOTOR_CONFIG *DC_MOTOR_structConfig ,u8 Copy_u8Direction) ;








#endif /* DC_MOTOR_INTERFACE_H_ */
