################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../rf24mesh/RF24Mesh.cpp 

OBJS += \
./rf24mesh/RF24Mesh.o 

CPP_DEPS += \
./rf24mesh/RF24Mesh.d 


# Each subdirectory must supply rules for building sources it contributes
rf24mesh/%.o: ../rf24mesh/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


