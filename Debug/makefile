################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/MUSART/subdir.mk
-include MCAL/MGIE/subdir.mk
-include MCAL/MDIO/subdir.mk
-include MCAL/MADC/subdir.mk
-include HAL/HSTEPPER/subdir.mk
-include HAL/HKPD/subdir.mk
-include HAL/HCLCD/subdir.mk
-include FreeRTOS/subdir.mk
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
integration_Test.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: integration_Test.elf secondary-outputs

# Tool invocations
integration_Test.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,integration_Test.map -mmcu=atmega32 -o "integration_Test.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

integration_Test.lss: integration_Test.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S integration_Test.elf  >"integration_Test.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: integration_Test.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 integration_Test.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) integration_Test.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
