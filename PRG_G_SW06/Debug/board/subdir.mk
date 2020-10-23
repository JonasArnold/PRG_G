################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/adc.c \
../board/board.c \
../board/clock_config.c \
../board/dac.c \
../board/delay.c \
../board/led.c \
../board/peripherals.c \
../board/pin_mux.c \
../board/pwm.c \
../board/sseg.c \
../board/sw.c \
../board/tilt.c 

OBJS += \
./board/adc.o \
./board/board.o \
./board/clock_config.o \
./board/dac.o \
./board/delay.o \
./board/led.o \
./board/peripherals.o \
./board/pin_mux.o \
./board/pwm.o \
./board/sseg.o \
./board/sw.o \
./board/tilt.o 

C_DEPS += \
./board/adc.d \
./board/board.d \
./board/clock_config.d \
./board/dac.d \
./board/delay.d \
./board/led.d \
./board/peripherals.d \
./board/pin_mux.d \
./board/pwm.d \
./board/sseg.d \
./board/sw.d \
./board/tilt.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I../board -I../source -I../drivers -I../device -I../CMSIS -I../component/serial_manager -I../component/lists -I../component/uart -I../utilities -O0 -fno-common -g3 -Wall -Wextra -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


