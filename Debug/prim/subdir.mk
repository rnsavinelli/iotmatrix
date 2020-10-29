################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../prim/prim_gpio.c \
../prim/prim_matrix.c \
../prim/prim_rtc.c \
../prim/prim_systick.c \
../prim/prim_uart.c 

OBJS += \
./prim/prim_gpio.o \
./prim/prim_matrix.o \
./prim/prim_rtc.o \
./prim/prim_systick.o \
./prim/prim_uart.o 

C_DEPS += \
./prim/prim_gpio.d \
./prim/prim_matrix.d \
./prim/prim_rtc.d \
./prim/prim_systick.d \
./prim/prim_uart.d 


# Each subdirectory must supply rules for building sources it contributes
prim/%.o: ../prim/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\User\Desktop\bibliotecaInfoII\include" -I"C:\Users\User\Documents\MCUXpressoIDE_11.0.0_2516\workspace\iotmatrix\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


