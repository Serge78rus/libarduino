################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rf24ethernet/utility/psock.c \
../rf24ethernet/utility/slipdev.c \
../rf24ethernet/utility/timer.c \
../rf24ethernet/utility/uip-fw.c \
../rf24ethernet/utility/uip-neighbor.c \
../rf24ethernet/utility/uip-split.c \
../rf24ethernet/utility/uip.c \
../rf24ethernet/utility/uip_arp.c \
../rf24ethernet/utility/uiplib.c 

CPP_SRCS += \
../rf24ethernet/utility/uip_debug.cpp 

OBJS += \
./rf24ethernet/utility/psock.o \
./rf24ethernet/utility/slipdev.o \
./rf24ethernet/utility/timer.o \
./rf24ethernet/utility/uip-fw.o \
./rf24ethernet/utility/uip-neighbor.o \
./rf24ethernet/utility/uip-split.o \
./rf24ethernet/utility/uip.o \
./rf24ethernet/utility/uip_arp.o \
./rf24ethernet/utility/uip_debug.o \
./rf24ethernet/utility/uiplib.o 

C_DEPS += \
./rf24ethernet/utility/psock.d \
./rf24ethernet/utility/slipdev.d \
./rf24ethernet/utility/timer.d \
./rf24ethernet/utility/uip-fw.d \
./rf24ethernet/utility/uip-neighbor.d \
./rf24ethernet/utility/uip-split.d \
./rf24ethernet/utility/uip.d \
./rf24ethernet/utility/uip_arp.d \
./rf24ethernet/utility/uiplib.d 

CPP_DEPS += \
./rf24ethernet/utility/uip_debug.d 


# Each subdirectory must supply rules for building sources it contributes
rf24ethernet/utility/%.o: ../rf24ethernet/utility/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

rf24ethernet/utility/%.o: ../rf24ethernet/utility/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


