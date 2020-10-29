################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MdESistema.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/fatfs.c \
../src/ffunicode.c \
../src/iotmatrix.c \
../src/rtc176x.c 

OBJS += \
./src/MdESistema.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/fatfs.o \
./src/ffunicode.o \
./src/iotmatrix.o \
./src/rtc176x.o 

C_DEPS += \
./src/MdESistema.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/fatfs.d \
./src/ffunicode.d \
./src/iotmatrix.d \
./src/rtc176x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\User\Desktop\bibliotecaInfoII\include" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\src" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\inc_sd" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\inc_sd" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\drivers" -I"C:\Users\User\Desktop\iotmatrix\iotmatrix\inc\prim" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


