################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Adafruit/Adafruit_BMP085.cpp 

OBJS += \
./Adafruit/Adafruit_BMP085.o 

CPP_DEPS += \
./Adafruit/Adafruit_BMP085.d 


# Each subdirectory must supply rules for building sources it contributes
Adafruit/%.o: ../Adafruit/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


