################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/CLC/CLC_program.c \
../HAL/CLC/calculate.c 

OBJS += \
./HAL/CLC/CLC_program.o \
./HAL/CLC/calculate.o 

C_DEPS += \
./HAL/CLC/CLC_program.d \
./HAL/CLC/calculate.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/CLC/%.o: ../HAL/CLC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


