/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL 		  *******************/
/*************** SWC: DC_Motor		  *******************/
/*************** Date: 18/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#include "BIT_Math.h"
#include "STD_TYPES.h"

#define F_CPU 8000000UL
#include <avr/delay.h>

#include "DIO_interface.h"
#include "DC_Motor_interface.h"

void DCMOTOR_voidInit(DCMOTOR_CONFIG *DC_MOTOR_structConfig)
{
	DIO_enumSetPinDirection(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinA,DCMOTOR_PIN_OUTPUT);
	DIO_enumSetPinDirection(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinB,DCMOTOR_PIN_OUTPUT);
}

u8 DCMOTOR_uint8ControlDirection (DCMOTOR_CONFIG *DC_MOTOR_structConfig ,u8 Copy_u8Direction)
{
	u8 Local_u8ReturnError = STD_TYPES_OK;

	switch(Copy_u8Direction)
	{
	case DCMOTOR_CW :
	{
		/*Set the clockwise direction and start Pin is low to avoid the short circuit*/
		DIO_enumSetPinValue(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinA,DCMOTOR_PIN_LOW);
		DIO_enumSetPinValue(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinB,DCMOTOR_PIN_HIGH);
		break;
	}
	case DCMOTOR_CCW :
	{
		/*Set the counter clockwise direction and start Pin is low to avoid the short circuit*/
		DIO_enumSetPinValue(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinB,DCMOTOR_PIN_LOW);
		DIO_enumSetPinValue(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinA,DCMOTOR_PIN_HIGH);
		break;
	}
	case DCMOTOR_STOP :
	{
		/*to stop the motor (break circuit)*/
		DIO_enumSetPinValue(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinB,DCMOTOR_PIN_LOW);
		DIO_enumSetPinValue(DC_MOTOR_structConfig->DcMotorPort,DC_MOTOR_structConfig->DcMotorPinA,DCMOTOR_PIN_LOW);
		break;
	}

	default : Local_u8ReturnError =STD_TYPES_NOK;
	}

	return Local_u8ReturnError;
}
