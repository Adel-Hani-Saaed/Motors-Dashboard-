/********************************************************/
/********************************************************/
/*************** Author: Adel_Hani	  *******************/
/*************** Layer: APP		 	  *******************/
/*************** SWC: DashBoard		  *******************/
/*************** Date: 2/4/2023 	  *******************/
/*************** Version: 2.00		  *******************/
/********************************************************/
/********************************************************/

#include "BIT_Math.h"
#include "STD_TYPES.h"
#include "Mapping_interface.h"

#define F_CPU  8000000UL
#include "util/delay.h"

#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "ADC_interface.h"
#include "Timer0_interface.h"
#include "Timer1_interface.h"


#include "Buzzer_interface.h"
#include "CLCD_interface.h"
#include "DC_Motor_interface.h"
#include "Keypad_interface.h"
#include "Led_interface.h"
#include "Servo_interface.h"
#include "Stepper_interface.h"

/*Callback function*/
void INT0ISR(void);
void INT1ISR(void);

u8 HamokshaChar[8] = {
		0b01110,
		0b01110,
		0b01110,
		0b00100,
		0b01110,
		0b10101,
		0b01110,
		0b10001
};

u8 Local_u8Start_closedSystem = 0;

u16 ConvertArrayToValue(u8 Copy_u8Number[], u8 Local_u8SizeNumber);
u8 Check_IdAndPass(u8 Arr_Id[] , u8 Arr_Pass[] , u8 Arr_CheckId[] , u8 Arr_CheckPass[] , u8 Size_u8ID,u8 Size_u8Pass,u8 Size_u8CheckID,u8 Size_u8CheckPass);


int main ()
{

	u8 Local_u8CounterLoginID = 0 ;				//counter for first array stored ID login
	u8 Local_u8CounterLoginPass = 0 ;			//counter for second array stored  pass login
	u8 Local_u8CounterCheckLoginID = 0 ;		//counter for check first array stored ID login
	u8 Local_u8CounterCheckLoginPass = 0 ;		//counter for check second array stored pass login
	u8 Local_u8ArrLoginID[8] ;					//to stored ID Member
	u8 Local_u8ArrLoginPass[8];					//to stored the password
	u8 Local_u8ArrCheckLoginID[8] ;				//check ID valid
	u8 Local_u8ArrCheckLoginPass[8];			//check PAss valid
	u8 Local_u8KeypadValue ;					//Local return check valued
	u16 Local_u16ReadingADCPotentiometer ;		//For reading Potentiometer
	u8 Local_u8CounterAngleServo=0;				//for counter stored the angle servo_motor
	u8 Local_u8AngleServo[3];					//for stored the angle servo_motor
	u8 Local_u8AngleSteeperValue[3];			//for stored the angle Stepper_motor
	u8 Local_u8SpeedValue = 0 ;			//Speed to u need in Stepper (from  2 to  9   is best values )
	u16 Local_u8ReturnValueAngle;				//the return function convert array to number

	/*objects for the two LED detector the system (Green -> Start & Red -> Closed)*/
	LED_T LED_RedClosedSys 		={LED_PORTD , LED_PIN1 ,LED_SOURCE };
	LED_T LED_GreenStartSys 	={LED_PORTD , LED_PIN0 ,LED_SOURCE };
	/*initialization The Pins To LED the System*/
	LED_voidPinInit		(&LED_GreenStartSys);
	LED_voidPinInit		(&LED_RedClosedSys);


	/*objects for the DCMotor & ADC*/
	DCMOTOR_CONFIG DC_MOTOR ={ DCMOTOR_PORTA , DCMOTOR_PIN6 , DCMOTOR_PIN7};
	DCMOTOR_voidInit(&DC_MOTOR);

	ADC_voidInit();



	/*initialization Timer0 Fast_PWM to control the Speed Motor and set Pin OC0 is output*/
	TIMER1_voidInit();
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);


	/*initialization Pin Servo_Motor connect with OCR1B*/
	SERVO_voidInit(SERVO_OC1B_PIN4);

	/*for External interrupt enable*/
	EXTI_voidINT0Init();
	EXTI_voidINT1Init();
	GIE_voidEnable();
	/*Pull_up in EXTI*/
	DIO_enumSetPinValue(DIO_PORTD,DIO_PIN2,DIO_HIGH);
	DIO_enumSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
	/*Registration Function*/
	EXTI_u8ExtISetCallBackINT0(&INT0ISR);
	EXTI_u8ExtISetCallBackINT1(&INT1ISR);


	/*initialization Timer0 Fast_PWM to control the Speed Motor and set Pin OC0 is output*/
	TIMER0_voidInit();
	DIO_enumSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);



	/*initialization LCD & Keypad & Stepper_Motor & DC_Motor */
	CLCD_voidInit();
	KPD_voidInit();
	STEPPER_voidInit();
	SERVO_voidInit(SERVO_OC1B_PIN4);



	while(1)
	{
		Local_u8CounterLoginID = 0 ;				//counter for first array stored pass login
		Local_u8CounterLoginPass = 0 ;				//counter for second array stored  pass
		Local_u8CounterCheckLoginID = 0 ;			//counter for first array stored pass login
		Local_u8CounterCheckLoginPass = 0 ;			//counter for second array stored  pass

		CLCD_voidClearLCD();


		if (Local_u8Start_closedSystem == 1)
		{
			LED_voidPinTurnOn(&LED_GreenStartSys);
			LED_voidPinTurnOff(&LED_RedClosedSys);
			CLCD_voidClearLCD();
			CLCD_voidSendString("Start System...");
			CLCD_voidSendStringPosition(" Welcome Member ",1,0);
			_delay_ms(2000);
			CLCD_voidClearLCD();


			/*To Register the Pass */
			CLCD_voidSendStringPosition("Login Member ID",0,0);
			/*Save the ID member*/
			while((Local_u8Start_closedSystem != 2))
			{
				/*wait for pressed key*/
				do{
					Local_u8KeypadValue = KPD_u8GetPressedKey();
				}while( Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

				/*enter is save the password*/
				if (Local_u8KeypadValue == '%'){ break; }

				/*print the valued in LCD*/
				CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterLoginID);
				_delay_ms(200);

				/*stored the valued in */
				Local_u8ArrLoginID[Local_u8CounterLoginID]=Local_u8KeypadValue;
				Local_u8CounterLoginID++;
			}


			/*Clear LCD and wait check password*/
			CLCD_voidClearLCD();
			CLCD_voidSendStringPosition("Enter Password", 0 , 0);
			Local_u8KeypadValue = KPD_NO_PRESSES_KEY;

			while(Local_u8KeypadValue != '%'  && (Local_u8Start_closedSystem != 2))
			{
				do{
					Local_u8KeypadValue=KPD_u8GetPressedKey();
				}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

				if (Local_u8KeypadValue == '%'){ break; }
				_delay_ms(100);
				CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterLoginPass);
				Local_u8ArrLoginPass[Local_u8CounterLoginPass]=Local_u8KeypadValue;
				Local_u8CounterLoginPass++;

			}


			CLCD_voidClearLCD();
			CLCD_voidSendStringPosition("Pleased Waiting..",0,0);
			CLCD_voidSendStringPosition("System Save Data", 1,0);
			_delay_ms(1000);
			CLCD_voidClearLCD();



			/*To Register the Pass */
			CLCD_voidSendStringPosition("Member ID ",0,0);
			/*Save the ID member*/
			while((Local_u8Start_closedSystem != 2))
			{
				/*wait for pressed key*/
				do{
					Local_u8KeypadValue = KPD_u8GetPressedKey();
				}while( Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

				/*enter is save the password*/
				if (Local_u8KeypadValue == '%'){ break; }

				/*print the valued in LCD*/
				CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterCheckLoginID);
				_delay_ms(200);

				/*stored the valued in */
				Local_u8ArrCheckLoginID[Local_u8CounterCheckLoginID]=Local_u8KeypadValue;
				Local_u8CounterCheckLoginID++;
			}


			/*Clear LCD and enter the pass*/
			CLCD_voidClearLCD();
			CLCD_voidSendStringPosition("Enter Password", 0 , 0);
			Local_u8KeypadValue = KPD_NO_PRESSES_KEY;

			while(Local_u8KeypadValue != '%'  && (Local_u8Start_closedSystem != 2))
			{
				do{
					Local_u8KeypadValue=KPD_u8GetPressedKey();
				}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

				if (Local_u8KeypadValue == '%'){ break; }
				_delay_ms(100);
				CLCD_voidSendCharPosition('*',1,Local_u8CounterCheckLoginPass);
				Local_u8ArrCheckLoginPass[Local_u8CounterCheckLoginPass]=Local_u8KeypadValue;
				Local_u8CounterCheckLoginPass++;
			}


			CLCD_voidClearLCD();

			/*Correct the Start System Id and Password*/
			if (Check_IdAndPass(Local_u8ArrLoginID, Local_u8ArrLoginPass, Local_u8ArrCheckLoginID, Local_u8ArrCheckLoginPass, Local_u8CounterLoginID, Local_u8CounterLoginPass, Local_u8CounterCheckLoginID, Local_u8CounterCheckLoginPass) && (Local_u8Start_closedSystem != 2))
			{
				CLCD_voidClearLCD();
				CLCD_voidSendStringPosition("Correct Pass&ID",0,0);
				CLCD_voidSendStringPosition("Welcome ID:",1,0);
				CLCD_voidPrintINTNumber(ConvertArrayToValue(Local_u8ArrLoginID, Local_u8CounterLoginID));
				_delay_ms(1000);



				CLCD_voidClearLCD();
				CLCD_voidSendStringPosition("Start Dash_board",0,0);

				for (u8 i = 0 ; i <15 ; i++)
				{
					CLCD_voidSpecialCharacter(HamokshaChar, 0, 1, i);
					CLCD_voidClearLCDPosition(1, i-1);
				}
				_delay_ms(300);
				for(u8 j = 15 ; j > 0;  j--)
				{
					CLCD_voidSpecialCharacter(HamokshaChar, 0, 1, j);
					CLCD_voidClearLCDPosition(1, j+1);
				}


				while((Local_u8Start_closedSystem != 2))
				{
					CLCD_voidClearLCD();
					_delay_ms(300);
					CLCD_voidSendStringPosition("1-DCMotor",0,0);
					CLCD_voidSendStringPosition("2-Stepper 3-Servo",1,0);

					/*Enter the Motor needed*/
					do{
						Local_u8KeypadValue=KPD_u8GetPressedKey();
					}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2) );

					/*DcMotor*/
					if (Local_u8KeypadValue == 1 && (Local_u8Start_closedSystem != 2))
					{
						CLCD_voidClearLCD();
						_delay_ms(200);
						CLCD_voidSendStringPosition("1-CW Direction", 0, 0);
						CLCD_voidSendStringPosition("2-CCW Direction", 1, 0);

						do{
							Local_u8KeypadValue=KPD_u8GetPressedKey();
						}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2) );

						u8 Local_u8MotorDir = Local_u8KeypadValue;

						CLCD_voidClearLCD();
						_delay_ms(200);
						CLCD_voidSendStringPosition("Speed Control", 0, 0);
						_delay_ms(500);
						CLCD_voidClearLCD();
						CLCD_voidSendStringPosition("1-FullSpeed ", 0, 0);
						CLCD_voidSendStringPosition("2-Pot 3-LM35", 1, 0);

						do{
							Local_u8KeypadValue=KPD_u8GetPressedKey();
						}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2) );

						u8 Local_u8SppedControlState = Local_u8KeypadValue;


						/*Full Speed*/
						if (Local_u8SppedControlState == 1 && (Local_u8Start_closedSystem != 2))
						{
							CLCD_voidClearLCD();
							_delay_ms(200);
							if (Local_u8MotorDir == 1 && (Local_u8Start_closedSystem != 2) )
							{
								DIO_enumSetPinValue(DIO_PORTB, DIO_PIN3, DIO_HIGH);
								DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_CW);
							}
							else if (Local_u8MotorDir == 2 && (Local_u8Start_closedSystem != 2) )
							{
								DIO_enumSetPinValue(DIO_PORTB, DIO_PIN3, DIO_HIGH);
								DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_CCW);
							}

							/*Enter any passed to return the List*/
							CLCD_voidClearLCD();
							_delay_ms(200);
							CLCD_voidSendStringIndex_16("Pressed Any Key to Stop DCMotor");

							do{
								Local_u8KeypadValue = KPD_u8GetPressedKey();
							}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

							DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_STOP);

						}

						/////////////////////////////////////////////////////////////////////
						/*Potentiometer */
						if (Local_u8SppedControlState == 2 && (Local_u8Start_closedSystem != 2))
						{

							while((Local_u8Start_closedSystem != 2))
							{
								CLCD_voidClearLCD();
								_delay_ms(200);
								if (Local_u8MotorDir == 1 )
								{
									ADC_u16StartConversionSynch(CHANNEL_A1, &Local_u16ReadingADCPotentiometer);
									TIMER0_voidSetCompMatchValue(MAPPING_s32GetOutput(0, 1024, 0, 255, Local_u16ReadingADCPotentiometer));
									DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_CW);
								}

								Local_u8KeypadValue = KPD_u8GetPressedKey();
								if (Local_u8KeypadValue != KPD_NO_PRESSES_KEY )
								{
									break;
								}

								else if (Local_u8MotorDir == 2 )
								{
									ADC_u16StartConversionSynch(CHANNEL_A1, &Local_u16ReadingADCPotentiometer);
									TIMER0_voidSetCompMatchValue(MAPPING_s32GetOutput(0, 1024, 0, 255, Local_u16ReadingADCPotentiometer));
									DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_CCW);
								}
								/*Enter any passed to return the List*/
								CLCD_voidSendStringIndex_16("Pressed Any Key to Stop DCMotor");
							}

							TIMER0_voidSetCompMatchValue(0);
							DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_STOP);
						}

						/*LM35*/
						if (Local_u8SppedControlState == 3 && (Local_u8Start_closedSystem != 2))
						{
							while((Local_u8Start_closedSystem != 2))
							{
								CLCD_voidClearLCD();
								_delay_ms(200);
								if (Local_u8MotorDir == 1 && (Local_u8Start_closedSystem != 2) )
								{
									ADC_u16StartConversionSynch(CHANNEL_A0, &Local_u16ReadingADCPotentiometer);
									TIMER0_voidSetCompMatchValue(MAPPING_s32GetOutput(0, 30, 0, 255, Local_u16ReadingADCPotentiometer));
									DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_CW);
								}

								Local_u8KeypadValue = KPD_u8GetPressedKey();
								if (Local_u8KeypadValue != KPD_NO_PRESSES_KEY)
								{
									break;
								}

								else if (Local_u8MotorDir == 2  && (Local_u8Start_closedSystem != 2))
								{
									ADC_u16StartConversionSynch(CHANNEL_A0, &Local_u16ReadingADCPotentiometer);
									TIMER0_voidSetCompMatchValue(MAPPING_s32GetOutput(0, 30, 0, 255, Local_u16ReadingADCPotentiometer));
									DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_CCW);
								}
								/*Enter any passed to return the List*/
								CLCD_voidSendStringIndex_16("Pressed Any Key to Stop DCMotor");
							}

							TIMER0_voidSetCompMatchValue(0);
							DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_STOP);
						}

						else
						{
							CLCD_voidClearLCD();
							_delay_ms(200);
							CLCD_voidSendStringIndex_16("Selection Control Speed Wrong");
							_delay_ms(1000);
						}
					}



					/*Stepper Motor*/
					if (Local_u8KeypadValue == 2 && (Local_u8Start_closedSystem != 2))
					{
						CLCD_voidClearLCD();
						CLCD_voidSendStringPosition("CW  Pass 1", 0, 0);
						CLCD_voidSendStringPosition("CCW Pass 2", 1, 0);

						u8 Local_u8CounterAngle = 0;

						/*Enter the Direction needed*/
						do{
							Local_u8KeypadValue=KPD_u8GetPressedKey();
						}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2) );

						/*CW*/
						if (Local_u8KeypadValue == 1 && (Local_u8Start_closedSystem != 2) )
						{
							CLCD_voidClearLCD();
							CLCD_voidSendStringPosition("Full STEP  1", 0, 0);
							CLCD_voidSendStringPosition("Half STEP  2", 1, 0);

							/*Enter the Type Step ( FULL / HALF ) Step */
							do{
								Local_u8KeypadValue=KPD_u8GetPressedKey();
							}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

							/*if Enter Full Step CW*/
							if (Local_u8KeypadValue == 1 && (Local_u8Start_closedSystem != 2) )
							{
								CLCD_voidClearLCD();
								CLCD_voidSendStringPosition("Select angle...", 0 , 0);

								/*Enter the Value the Angle to u needed*/
								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2) );

									if (Local_u8KeypadValue == '%')
									{
										break;
									}

									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterAngle);
									_delay_ms(200);

									/*stored the valued in */
									Local_u8AngleSteeperValue[Local_u8CounterAngle]=Local_u8KeypadValue;
									Local_u8CounterAngle++;
								}


								CLCD_voidClearLCD();
								CLCD_voidSendString("Enter the Speed");
								CLCD_voidGoToXY(1, 0);
								CLCD_voidSendString("from 2 to 9 : ");

								/*Enter the Speed Rate u needed the Best speed is (from 2 to  9  )*/
								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY  && (Local_u8Start_closedSystem != 2));

									if (Local_u8KeypadValue == '%')
									{
										break;
									}
									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,14);
									_delay_ms(200);

									Local_u8SpeedValue = Local_u8KeypadValue;
								}

								/*Return the convert the array Storage the value to return the value number */
								Local_u8ReturnValueAngle = ConvertArrayToValue(Local_u8AngleSteeperValue,Local_u8CounterAngle );

								/*The motor start move*/
								STEPPER_voidTurnOn(STEPPER_FULL_STEP , STEPPER_CLOCK_WISE , Local_u8SpeedValue , Local_u8ReturnValueAngle);
								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Angle reached");
								_delay_ms(1000);
								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Pressed Any Key to return List");

								/*Enter any Key to return the list*/
								do{
									Local_u8KeypadValue = KPD_u8GetPressedKey();
								}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));
							}

							/*HalfStep CW*/
							if (Local_u8KeypadValue == 2 && (Local_u8Start_closedSystem != 2) )
							{
								CLCD_voidClearLCD();
								CLCD_voidSendStringPosition("Select angle...", 0 , 0);

								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

									if (Local_u8KeypadValue == '%')
									{
										break;
									}
									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterAngle);
									_delay_ms(200);

									/*stored the valued in */
									Local_u8AngleSteeperValue[Local_u8CounterAngle]=Local_u8KeypadValue;
									Local_u8CounterAngle++;
								}
								CLCD_voidClearLCD();
								CLCD_voidSendString("Enter the Speed");
								CLCD_voidGoToXY(1, 0);
								CLCD_voidSendString("from 2 to 9 : ");
								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY );

									if (Local_u8KeypadValue == '%')
									{
										break;
									}

									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,14);
									_delay_ms(200);
									Local_u8SpeedValue = Local_u8KeypadValue;
								}
								Local_u8ReturnValueAngle = ConvertArrayToValue(Local_u8AngleSteeperValue,Local_u8CounterAngle );
								STEPPER_voidTurnOn(STEPPER_HALF_STEP , STEPPER_CLOCK_WISE , Local_u8SpeedValue , Local_u8ReturnValueAngle) ;

								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Angle reached");
								_delay_ms(1000);
								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Pressed Any Key to return List");

								do{
									Local_u8KeypadValue = KPD_u8GetPressedKey();
								}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY);

								STEPPER_voidTurnOff();
								_delay_ms(500);

							}
						}


						/*CCW Stepper Motor*/
						if (Local_u8KeypadValue == 2 && (Local_u8Start_closedSystem != 2) )
						{
							CLCD_voidClearLCD();
							CLCD_voidSendStringPosition("Full STEP  1", 0, 0);
							CLCD_voidSendStringPosition("Half STEP  2", 1, 0);

							do{
								Local_u8KeypadValue=KPD_u8GetPressedKey();
							}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY);

							/*Full Step CCW*/
							if (Local_u8KeypadValue == 1 && (Local_u8Start_closedSystem != 2) )
							{
								CLCD_voidClearLCD();
								CLCD_voidSendStringPosition("Select angle...", 0 , 0);

								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY );

									if (Local_u8KeypadValue == '%')
									{
										break;
									}


									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterAngle);
									_delay_ms(200);

									/*stored the valued in */
									Local_u8AngleSteeperValue[Local_u8CounterAngle]=Local_u8KeypadValue;
									Local_u8CounterAngle++;

								}
								CLCD_voidClearLCD();
								CLCD_voidSendString("Enter the Speed");
								CLCD_voidGoToXY(1, 0);
								CLCD_voidSendString("from 2 to 9 : ");

								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY );

									if (Local_u8KeypadValue == '%')
									{
										break;
									}


									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,14);
									_delay_ms(200);

									Local_u8SpeedValue = Local_u8KeypadValue;

								}

								Local_u8ReturnValueAngle = ConvertArrayToValue(Local_u8AngleSteeperValue,Local_u8CounterAngle );
								STEPPER_voidTurnOn(STEPPER_FULL_STEP , STEPPER_ANTI_CLOCK_WISE , Local_u8SpeedValue , Local_u8ReturnValueAngle) ;


								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Angle reached");
								_delay_ms(1000);
								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Pressed Any Key to return List");

								do{
									Local_u8KeypadValue = KPD_u8GetPressedKey();
								}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY);

								STEPPER_voidTurnOff();
								_delay_ms(500);
								CLCD_voidClearLCD();
							}


							/*HalfStep CCW*/
							if (Local_u8KeypadValue == 2 && (Local_u8Start_closedSystem != 2) )
							{
								CLCD_voidClearLCD();
								CLCD_voidSendStringPosition("Select angle...", 0 , 0);
								while( (Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY  );

									if (Local_u8KeypadValue == '%' && (Local_u8Start_closedSystem != 2))
									{
										break;
									}
									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterAngle);
									_delay_ms(200);
									/*stored the valued in */
									Local_u8AngleSteeperValue[Local_u8CounterAngle]=Local_u8KeypadValue;
									Local_u8CounterAngle++;
								}
								CLCD_voidClearLCD();
								CLCD_voidSendString("Enter the Speed");
								CLCD_voidGoToXY(1, 0);
								CLCD_voidSendString("from 2 to 9 : ");

								while((Local_u8Start_closedSystem != 2) )
								{
									do{
										Local_u8KeypadValue=KPD_u8GetPressedKey();
									}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY );

									if (Local_u8KeypadValue == '%')
									{
										break;
									}
									/*print the valued in LCD*/
									CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,14);
									_delay_ms(200);
									Local_u8SpeedValue = Local_u8KeypadValue;
								}

								Local_u8ReturnValueAngle = ConvertArrayToValue(Local_u8AngleSteeperValue,Local_u8CounterAngle );
								STEPPER_voidTurnOn(STEPPER_HALF_STEP , STEPPER_ANTI_CLOCK_WISE , Local_u8SpeedValue , Local_u8ReturnValueAngle) ;

								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Angle reached");
								_delay_ms(1000);
								CLCD_voidClearLCD();
								CLCD_voidSendStringIndex_16("Pressed Any Key to return List");

								do{
									Local_u8KeypadValue = KPD_u8GetPressedKey();
								}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY);

								STEPPER_voidTurnOff();
								_delay_ms(500);
							}
						}
					}


					/*Servo Motor*/
					Local_u8CounterAngleServo=0;
					if (Local_u8KeypadValue == 3 && (Local_u8Start_closedSystem != 2))
					{
						CLCD_voidClearLCD();
						CLCD_voidSendStringPosition("Select Angle", 0, 0);
						while((Local_u8Start_closedSystem != 2))
						{
							/*wait for pressed key*/
							do{
								Local_u8KeypadValue = KPD_u8GetPressedKey();
							}while( Local_u8KeypadValue == KPD_NO_PRESSES_KEY && (Local_u8Start_closedSystem != 2));

							/*enter is save the password*/
							if (Local_u8KeypadValue == '%'){ break; }

							/*print the valued in LCD*/
							CLCD_voidSendINTNumberPosition(Local_u8KeypadValue,1,Local_u8CounterAngleServo);
							_delay_ms(200);

							/*stored the valued in */
							Local_u8AngleServo[Local_u8CounterAngleServo]=Local_u8KeypadValue;
							Local_u8CounterAngleServo++;
						}

						u8 ValueAngle = ConvertArrayToValue(Local_u8AngleServo, Local_u8CounterAngleServo);
						SERVO_voidSetDegreeRotate(SERVO_OC1B_PIN4, ValueAngle);
						_delay_ms(1000);

						CLCD_voidClearLCD();
						CLCD_voidSendStringPosition("Angle reached", 0, 0);

						_delay_ms(1000);
						CLCD_voidClearLCD();
						CLCD_voidSendStringIndex_16("Pressed Any Key to return List");

						do{
							Local_u8KeypadValue = KPD_u8GetPressedKey();
						}while(Local_u8KeypadValue == KPD_NO_PRESSES_KEY);
					}
				}
			}
			/*Wrong the Repeated Id and Password*/
			else
			{
				CLCD_voidClearLCD();
				CLCD_voidSendStringPosition("Wrong Pass & ID",0,0);
				_delay_ms(5000);
				CLCD_voidClearLCD();
			}
		}

		/*Closed System*/
		else if (Local_u8Start_closedSystem == 2)
		{
			/*Turn_off the motors and led green and turn_on led red*/
			LED_voidPinTurnOn(&LED_RedClosedSys);
			LED_voidPinTurnOff(&LED_GreenStartSys);
			DCMOTOR_uint8ControlDirection(&DC_MOTOR, DCMOTOR_STOP);
			STEPPER_voidTurnOff();
			SERVO_voidSetDegreeRotate(SERVO_OC1B_PIN4, 0);

			CLCD_voidClearLCD();
			CLCD_voidSendString("Bye Bye.....");
			_delay_ms(2000);
			CLCD_voidClearLCD();

			Local_u8Start_closedSystem = 3;
		}
	}
	return 0 ;
}


/*Start ISR*/
void INT0ISR(void)
{
	Local_u8Start_closedSystem = 1;
}
/*Closed ISR*/
void INT1ISR(void)
{
	Local_u8Start_closedSystem = 2;
}


/*Function convert the array number to the value number and return the angle stepper motor */
u16 ConvertArrayToValue(u8 Copy_u8Number[], u8 Local_u8SizeNumber)
{
	u16 Number = Copy_u8Number[0];

	for (u8 counter=1 ; counter < Local_u8SizeNumber ; counter++)
	{
		Number = (Number*10) +Copy_u8Number[counter];
	}

	return Number;
}

u8 Check_IdAndPass(u8 Arr_Id[] , u8 Arr_Pass[] , u8 Arr_CheckId[] , u8 Arr_CheckPass[] , u8 Size_u8ID,u8 Size_u8Pass,u8 Size_u8CheckID,u8 Size_u8CheckPass)
{
	u8 Local_u8Return = STD_TYPES_OK;
	u8 Local_CountChar_1 = 0;
	u8 Local_CountChar_2 = 0;

	/*Check for Id */
	if (Size_u8ID == Size_u8CheckID)
	{
		for (u8 Local_counter = 0 ;  Local_counter<Size_u8ID ;Local_counter++ )
		{
			if (Arr_Id[Local_counter] == Arr_CheckId[Local_counter])
			{
				Local_CountChar_1++;
			}
		}
	}
	/*Check for Password */
	if (Size_u8Pass == Size_u8CheckPass)
	{
		for (u8 Local_counter_2 = 0 ;  Local_counter_2<Size_u8Pass ;Local_counter_2++ )
		{
			if (Arr_Pass[Local_counter_2] == Arr_CheckPass[Local_counter_2])
			{
				Local_CountChar_2++;
			}
		}
	}
	/*Return if The check Id & Pass is correct return 1 */
	if (Local_CountChar_1 == Size_u8ID)
	{
		if (Local_CountChar_2 == Size_u8Pass)
		{
			return Local_u8Return;
		}
	}
	/*Return if The check Id & Pass is Wrong return 0*/
	return STD_TYPES_NOK;
}

