################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../modbus/modbus_master.cpp \
../modbus/modbus_slave.cpp 

OBJS += \
./modbus/modbus_master.o \
./modbus/modbus_slave.o 

CPP_DEPS += \
./modbus/modbus_master.d \
./modbus/modbus_slave.d 


# Each subdirectory must supply rules for building sources it contributes
modbus/%.o: ../modbus/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=8000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


