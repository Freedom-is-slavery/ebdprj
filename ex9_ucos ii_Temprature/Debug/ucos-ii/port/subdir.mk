################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../ucos-ii/port/os_cpu_a.s 

C_SRCS += \
../ucos-ii/port/os_cpu_c.c \
../ucos-ii/port/os_dbg.c 

OBJS += \
./ucos-ii/port/os_cpu_a.o \
./ucos-ii/port/os_cpu_c.o \
./ucos-ii/port/os_dbg.o 

C_DEPS += \
./ucos-ii/port/os_cpu_c.d \
./ucos-ii/port/os_dbg.d 


# Each subdirectory must supply rules for building sources it contributes
ucos-ii/port/%.o: ../ucos-ii/port/%.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -I../ucos-ii -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
ucos-ii/port/os_cpu_c.o: ../ucos-ii/port/os_cpu_c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../ucos-ii/config -I../ucos-ii/port -I../ucos-ii/src -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/port/os_cpu_c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/port/os_dbg.o: ../ucos-ii/port/os_dbg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../ucos-ii/config -I../ucos-ii/port -I../ucos-ii/src -I../Drivers/CMSIS/Include -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/port/os_dbg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

