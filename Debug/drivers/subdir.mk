################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/driv_gpio.c \
../drivers/driv_matrix.c \
../drivers/driv_rtc.c \
../drivers/driv_spi.c \
../drivers/driv_systick.c \
../drivers/driv_uart.c \
../drivers/ff.c \
../drivers/ffunicode.c 

OBJS += \
./drivers/driv_gpio.o \
./drivers/driv_matrix.o \
./drivers/driv_rtc.o \
./drivers/driv_spi.o \
./drivers/driv_systick.o \
./drivers/driv_uart.o \
./drivers/ff.o \
./drivers/ffunicode.o 

C_DEPS += \
./drivers/driv_gpio.d \
./drivers/driv_matrix.d \
./drivers/driv_rtc.d \
./drivers/driv_spi.d \
./drivers/driv_systick.d \
./drivers/driv_uart.d \
./drivers/ff.d \
./drivers/ffunicode.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\User\Desktop\bibliotecaInfoII\include" -I"C:\Users\User\Documents\MCUXpressoIDE_11.0.0_2516\workspace\iotmatrix\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


