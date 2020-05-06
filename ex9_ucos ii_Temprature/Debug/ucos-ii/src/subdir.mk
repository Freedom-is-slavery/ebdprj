################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ucos-ii/src/os_core.c \
../ucos-ii/src/os_flag.c \
../ucos-ii/src/os_mbox.c \
../ucos-ii/src/os_mem.c \
../ucos-ii/src/os_mutex.c \
../ucos-ii/src/os_q.c \
../ucos-ii/src/os_sem.c \
../ucos-ii/src/os_task.c \
../ucos-ii/src/os_time.c \
../ucos-ii/src/os_tmr.c 

OBJS += \
./ucos-ii/src/os_core.o \
./ucos-ii/src/os_flag.o \
./ucos-ii/src/os_mbox.o \
./ucos-ii/src/os_mem.o \
./ucos-ii/src/os_mutex.o \
./ucos-ii/src/os_q.o \
./ucos-ii/src/os_sem.o \
./ucos-ii/src/os_task.o \
./ucos-ii/src/os_time.o \
./ucos-ii/src/os_tmr.o 

C_DEPS += \
./ucos-ii/src/os_core.d \
./ucos-ii/src/os_flag.d \
./ucos-ii/src/os_mbox.d \
./ucos-ii/src/os_mem.d \
./ucos-ii/src/os_mutex.d \
./ucos-ii/src/os_q.d \
./ucos-ii/src/os_sem.d \
./ucos-ii/src/os_task.d \
./ucos-ii/src/os_time.d \
./ucos-ii/src/os_tmr.d 


# Each subdirectory must supply rules for building sources it contributes
ucos-ii/src/os_core.o: ../ucos-ii/src/os_core.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_core.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_flag.o: ../ucos-ii/src/os_flag.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_flag.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_mbox.o: ../ucos-ii/src/os_mbox.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_mbox.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_mem.o: ../ucos-ii/src/os_mem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_mem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_mutex.o: ../ucos-ii/src/os_mutex.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_mutex.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_q.o: ../ucos-ii/src/os_q.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_q.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_sem.o: ../ucos-ii/src/os_sem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_sem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_task.o: ../ucos-ii/src/os_task.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_task.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_time.o: ../ucos-ii/src/os_time.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_time.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ucos-ii/src/os_tmr.o: ../ucos-ii/src/os_tmr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../ucos-ii/src -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../ucos-ii/port -I../ucos-ii/config -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ucos-ii/src/os_tmr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

