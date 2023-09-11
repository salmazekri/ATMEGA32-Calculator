################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/WatchDog/subdir.mk
-include MCAL/USART/subdir.mk
-include MCAL/TWI_Driver/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/ServoMotor/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KPD/subdir.mk
-include HAL/EEPROM_Handler/subdir.mk
-include HAL/CLC/subdir.mk
-include HAL/7Segments/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
priority_calc.lss \

FLASH_IMAGE += \
priority_calc.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: priority_calc.elf secondary-outputs

# Tool invocations
priority_calc.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,priority_calc.map -mmcu=atmega32 -o "priority_calc.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

priority_calc.lss: priority_calc.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S priority_calc.elf  >"priority_calc.lss"
	@echo 'Finished building: $@'
	@echo ' '

priority_calc.hex: priority_calc.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex priority_calc.elf  "priority_calc.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: priority_calc.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 priority_calc.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) priority_calc.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
