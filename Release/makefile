################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/q_learning/subdir.mk
-include arduino/core/avr-libc/subdir.mk
-include arduino/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/Users/marek/Workspaces/arduino/q_learning/Release/arduino.ar \

ELF += \
q_learning.elf \

EEP += \
q_learning.eep \

FLASH_IMAGE += \
q_learning.hex \


# All Target
all: q_learning

# Tool invocations
q_learning: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-size" -A "/Users/marek/Workspaces/arduino/q_learning/Release/q_learning.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/Users/marek/Workspaces/arduino/q_learning/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar" rcs "/Users/marek/Workspaces/arduino/q_learning/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

q_learning.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p -o "/Users/marek/Workspaces/arduino/q_learning/Release/q_learning.elf"   $(LINK_OBJ) $(AR)  "/Users/marek/Workspaces/arduino/q_learning/Release/arduino.ar" "-L/Users/marek/Workspaces/arduino/q_learning/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

q_learning.eep: $(ELF)
	@echo 'Create eeprom image'
	"/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "/Users/marek/Workspaces/arduino/q_learning/Release/q_learning.elf" "/Users/marek/Workspaces/arduino/q_learning/Release/q_learning.eep"
	@echo 'Finished building: $@'
	@echo ' '

q_learning.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom "/Users/marek/Workspaces/arduino/q_learning/Release/q_learning.elf" "/Users/marek/Workspaces/arduino/q_learning/Release/q_learning.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) q_learning
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
