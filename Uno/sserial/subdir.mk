################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sserial/SoftwareSerial.cpp 

OBJS += \
./sserial/SoftwareSerial.o 

CPP_DEPS += \
./sserial/SoftwareSerial.d 


# Each subdirectory must supply rules for building sources it contributes
sserial/%.o: ../sserial/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


