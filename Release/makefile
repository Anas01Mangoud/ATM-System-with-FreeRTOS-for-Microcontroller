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
integration_Tes.lss \

FLASH_IMAGE += \
integration_Tes.hex \

EEPROM_IMAGE += \
integration_Tes.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: integration_Tes.elf secondary-outputs

# Tool invocations
integration_Tes.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,integration_Tes.map -mmcu=atmega32 -o "integration_Tes.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

integration_Tes.lss: integration_Tes.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S integration_Tes.elf  >"integration_Tes.lss"
	@echo 'Finished building: $@'
	@echo ' '

integration_Tes.hex: integration_Tes.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex integration_Tes.elf  "integration_Tes.hex"
	@echo 'Finished building: $@'
	@echo ' '

integration_Tes.eep: integration_Tes.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex integration_Tes.elf  "integration_Tes.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: integration_Tes.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 integration_Tes.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) integration_Tes.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
