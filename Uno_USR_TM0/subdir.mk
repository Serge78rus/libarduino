################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../WInterrupts.c \
../hooks.c \
../wiring.c \
../wiring_analog.c \
../wiring_digital.c \
../wiring_pulse.c \
../wiring_shift.c 

CPP_SRCS += \
../CDC.cpp \
../HID.cpp \
../HardwareSerial.cpp \
../HardwareSerial0.cpp \
../HardwareSerial1.cpp \
../HardwareSerial2.cpp \
../HardwareSerial3.cpp \
../IPAddress.cpp \
../Print.cpp \
../Stream.cpp \
../Tone.cpp \
../USBCore.cpp \
../WMath.cpp \
../WString.cpp \
../abi.cpp \
../main.cpp \
../new.cpp 

OBJS += \
./CDC.o \
./HID.o \
./HardwareSerial.o \
./HardwareSerial0.o \
./HardwareSerial1.o \
./HardwareSerial2.o \
./HardwareSerial3.o \
./IPAddress.o \
./Print.o \
./Stream.o \
./Tone.o \
./USBCore.o \
./WInterrupts.o \
./WMath.o \
./WString.o \
./abi.o \
./hooks.o \
./main.o \
./new.o \
./wiring.o \
./wiring_analog.o \
./wiring_digital.o \
./wiring_pulse.o \
./wiring_shift.o 

C_DEPS += \
./WInterrupts.d \
./hooks.d \
./wiring.d \
./wiring_analog.d \
./wiring_digital.d \
./wiring_pulse.d \
./wiring_shift.d 

CPP_DEPS += \
./CDC.d \
./HID.d \
./HardwareSerial.d \
./HardwareSerial0.d \
./HardwareSerial1.d \
./HardwareSerial2.d \
./HardwareSerial3.d \
./IPAddress.d \
./Print.d \
./Stream.d \
./Tone.d \
./USBCore.d \
./WMath.d \
./WString.d \
./abi.d \
./main.d \
./new.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


