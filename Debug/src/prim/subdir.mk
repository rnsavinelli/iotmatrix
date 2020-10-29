################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/prim/prim_dataprocess.c \
../src/prim/prim_gpio.c \
../src/prim/prim_matrix.c \
../src/prim/prim_rtc.c \
../src/prim/prim_systick.c \
../src/prim/prim_uart.c 

OBJS += \
./src/prim/prim_dataprocess.o \
./src/prim/prim_gpio.o \
./src/prim/prim_matrix.o \
./src/prim/prim_rtc.o \
./src/prim/prim_systick.o \
./src/prim/prim_uart.o 

C_DEPS += \
./src/prim/prim_dataprocess.d \
./src/prim/prim_gpio.d \
./src/prim/prim_matrix.d \
./src/prim/prim_rtc.d \
./src/prim/prim_systick.d \
./src/prim/prim_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/prim/%.o: ../src/prim/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\User\Desktop\bibliotecaInfoII\include" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\src" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\inc_sd" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\inc_sd" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\drivers" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\prim" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


