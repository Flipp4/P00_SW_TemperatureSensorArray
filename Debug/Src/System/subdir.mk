################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/System/main.c \
../Src/System/stm32f4xx_hal_msp.c \
../Src/System/stm32f4xx_it.c \
../Src/System/syscalls.c \
../Src/System/sysmem.c \
../Src/System/system_stm32f4xx.c \
../Src/System/usb_device.c \
../Src/System/usbd_cdc_if.c \
../Src/System/usbd_conf.c \
../Src/System/usbd_desc.c 

OBJS += \
./Src/System/main.o \
./Src/System/stm32f4xx_hal_msp.o \
./Src/System/stm32f4xx_it.o \
./Src/System/syscalls.o \
./Src/System/sysmem.o \
./Src/System/system_stm32f4xx.o \
./Src/System/usb_device.o \
./Src/System/usbd_cdc_if.o \
./Src/System/usbd_conf.o \
./Src/System/usbd_desc.o 

C_DEPS += \
./Src/System/main.d \
./Src/System/stm32f4xx_hal_msp.d \
./Src/System/stm32f4xx_it.d \
./Src/System/syscalls.d \
./Src/System/sysmem.d \
./Src/System/system_stm32f4xx.d \
./Src/System/usb_device.d \
./Src/System/usbd_cdc_if.d \
./Src/System/usbd_conf.d \
./Src/System/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/System/%.o: ../Src/System/%.c Src/System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

