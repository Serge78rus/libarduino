################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mysensor/utility/LowPower.cpp \
../mysensor/utility/MsTimer2.cpp \
../mysensor/utility/RF24.cpp 

OBJS += \
./mysensor/utility/LowPower.o \
./mysensor/utility/MsTimer2.o \
./mysensor/utility/RF24.o 

CPP_DEPS += \
./mysensor/utility/LowPower.d \
./mysensor/utility/MsTimer2.d \
./mysensor/utility/RF24.d 


# Each subdirectory must supply rules for building sources it contributes
mysensor/utility/%.o: ../mysensor/utility/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


