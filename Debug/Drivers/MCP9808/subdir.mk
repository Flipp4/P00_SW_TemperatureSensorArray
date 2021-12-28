################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/MCP9808/MCP9808_ArrayData.c \
../Drivers/MCP9808/TemperatureSensor_MCP9808.c 

OBJS += \
./Drivers/MCP9808/MCP9808_ArrayData.o \
./Drivers/MCP9808/TemperatureSensor_MCP9808.o 

C_DEPS += \
./Drivers/MCP9808/MCP9808_ArrayData.d \
./Drivers/MCP9808/TemperatureSensor_MCP9808.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/MCP9808/%.o: ../Drivers/MCP9808/%.c Drivers/MCP9808/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

