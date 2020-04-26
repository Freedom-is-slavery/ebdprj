################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include ucos-ii/src/subdir.mk
-include ucos-ii/port/subdir.mk
-include ucos-ii/config/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ex8_ucos\ ii.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ex8_ucos\ ii.list \

OBJCOPY_BIN += \
ex8_ucos\ ii.bin \


# All Target
all: ex8_ucos\ ii.elf secondary-outputs

# Tool invocations
ex8_ucos\ ii.elf: $(OBJS) $(USER_OBJS) C:\Users\admin\Desktop\STM32_test\ebdprj\ex8_ucos\ ii\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "ex8_ucos ii.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\admin\Desktop\STM32_test\ebdprj\ex8_ucos ii\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ex8_ucos ii.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ex8_ucos\ ii.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ex8_ucos ii.list"
	@echo 'Finished building: $@'
	@echo ' '

ex8_ucos\ ii.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ex8_ucos ii.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
