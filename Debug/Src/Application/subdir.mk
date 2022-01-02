################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Application/Application.c \
../Src/Application/DataHandler.c \
../Src/Application/EventSystem.c \
../Src/Application/HandlesAssigner.c \
../Src/Application/ModuleInterconnect.c \
../Src/Application/TemperatureCollector.c 

OBJS += \
./Src/Application/Application.o \
./Src/Application/DataHandler.o \
./Src/Application/EventSystem.o \
./Src/Application/HandlesAssigner.o \
./Src/Application/ModuleInterconnect.o \
./Src/Application/TemperatureCollector.o 

C_DEPS += \
./Src/Application/Application.d \
./Src/Application/DataHandler.d \
./Src/Application/EventSystem.d \
./Src/Application/HandlesAssigner.d \
./Src/Application/ModuleInterconnect.d \
./Src/Application/TemperatureCollector.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Application/Application.o: ../Src/Application/Application.c Src/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -Wextra -Wswitch-default -Wswitch-enum -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/Application/%.o: ../Src/Application/%.c Src/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

