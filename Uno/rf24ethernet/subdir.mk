################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rf24ethernet/clock-arch.c 

CPP_SRCS += \
../rf24ethernet/Dns.cpp \
../rf24ethernet/RF24Client.cpp \
../rf24ethernet/RF24Ethernet.cpp \
../rf24ethernet/RF24Server.cpp \
../rf24ethernet/RF24Udp.cpp 

OBJS += \
./rf24ethernet/Dns.o \
./rf24ethernet/RF24Client.o \
./rf24ethernet/RF24Ethernet.o \
./rf24ethernet/RF24Server.o \
./rf24ethernet/RF24Udp.o \
./rf24ethernet/clock-arch.o 

C_DEPS += \
./rf24ethernet/clock-arch.d 

CPP_DEPS += \
./rf24ethernet/Dns.d \
./rf24ethernet/RF24Client.d \
./rf24ethernet/RF24Ethernet.d \
./rf24ethernet/RF24Server.d \
./rf24ethernet/RF24Udp.d 


# Each subdirectory must supply rules for building sources it contributes
rf24ethernet/%.o: ../rf24ethernet/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

rf24ethernet/%.o: ../rf24ethernet/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -Wall -Os -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


