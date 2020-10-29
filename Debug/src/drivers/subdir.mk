################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/driv_gpio.c \
../src/drivers/driv_matrix.c \
../src/drivers/driv_rtc.c \
../src/drivers/driv_spi.c \
../src/drivers/driv_systick.c \
../src/drivers/driv_uart.c 

OBJS += \
./src/drivers/driv_gpio.o \
./src/drivers/driv_matrix.o \
./src/drivers/driv_rtc.o \
./src/drivers/driv_spi.o \
./src/drivers/driv_systick.o \
./src/drivers/driv_uart.o 

C_DEPS += \
./src/drivers/driv_gpio.d \
./src/drivers/driv_matrix.d \
./src/drivers/driv_rtc.d \
./src/drivers/driv_spi.d \
./src/drivers/driv_systick.d \
./src/drivers/driv_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/%.o: ../src/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\User\Desktop\bibliotecaInfoII\include" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\src" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\inc_sd" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\inc_sd" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\drivers" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\prim" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


