################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ucos-ii/config/app_hooks.c 

OBJS += \
./ucos-ii/config/app_hooks.o 

C_DEPS += \
./ucos-ii/config/app_hooks.d 


# Each subdirectory must supply rules for building sources it contributes
ucos-ii/config/app_hooks.o: ../ucos-ii/config/app_hooks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../ucos-ii/config -I../ucos-ii/port -I../ucos-ii/src -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/config/app_hooks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

