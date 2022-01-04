################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Signal\ processing/Filters.c 

OBJS += \
./Src/Signal\ processing/Filters.o 

C_DEPS += \
./Src/Signal\ processing/Filters.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Signal\ processing/Filters.o: ../Src/Signal\ processing/Filters.c Src/Signal\ processing/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FatFs/src -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/Signal processing/Filters.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Signal-20-processing

clean-Src-2f-Signal-20-processing:
	-$(RM) ./Src/Signal\ processing/Filters.d ./Src/Signal\ processing/Filters.o

.PHONY: clean-Src-2f-Signal-20-processing

