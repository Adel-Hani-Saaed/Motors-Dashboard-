################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Porject/ADC_program.c \
../Porject/Buzzer_program.c \
../Porject/CLCD_program.c \
../Porject/DC_Motor_program.c \
../Porject/DIO_program.c \
../Porject/EXTI_program.c \
../Porject/GIE_program.c \
../Porject/Keypad_program.c \
../Porject/LM35_program.c \
../Porject/Led_program.c \
../Porject/Mapping_program.c \
../Porject/Pass_prog.c \
../Porject/Servo_program.c \
../Porject/Stepper_program.c \
../Porject/Timer0_program.c \
../Porject/Timer1_program.c \
../Porject/main.c 

OBJS += \
./Porject/ADC_program.o \
./Porject/Buzzer_program.o \
./Porject/CLCD_program.o \
./Porject/DC_Motor_program.o \
./Porject/DIO_program.o \
./Porject/EXTI_program.o \
./Porject/GIE_program.o \
./Porject/Keypad_program.o \
./Porject/LM35_program.o \
./Porject/Led_program.o \
./Porject/Mapping_program.o \
./Porject/Pass_prog.o \
./Porject/Servo_program.o \
./Porject/Stepper_program.o \
./Porject/Timer0_program.o \
./Porject/Timer1_program.o \
./Porject/main.o 

C_DEPS += \
./Porject/ADC_program.d \
./Porject/Buzzer_program.d \
./Porject/CLCD_program.d \
./Porject/DC_Motor_program.d \
./Porject/DIO_program.d \
./Porject/EXTI_program.d \
./Porject/GIE_program.d \
./Porject/Keypad_program.d \
./Porject/LM35_program.d \
./Porject/Led_program.d \
./Porject/Mapping_program.d \
./Porject/Pass_prog.d \
./Porject/Servo_program.d \
./Porject/Stepper_program.d \
./Porject/Timer0_program.d \
./Porject/Timer1_program.d \
./Porject/main.d 


# Each subdirectory must supply rules for building sources it contributes
Porject/%.o: ../Porject/%.c Porject/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


