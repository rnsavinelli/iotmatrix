################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/prim/subdir.mk
-include src/drivers/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: iotmatrix.axf

# Tool invocations
iotmatrix.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\jipic\Documents\temporalWorkdir\proyectoInfo2\bibliotecaInfoII\bin" -L"C:\Users\User\Desktop\bibliotecaInfoII\bin" -Xlinker -Map="iotmatrix.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "iotmatrix_Debug.ld" -o "iotmatrix.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) iotmatrix.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "iotmatrix.axf"; # arm-none-eabi-objcopy -v -O binary "iotmatrix.axf" "iotmatrix.bin" ; # checksum -p LPC1769 -d "iotmatrix.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
