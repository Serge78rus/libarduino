################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ethercard/EtherCard.cpp \
../ethercard/dhcp.cpp \
../ethercard/dns.cpp \
../ethercard/enc28j60.cpp \
../ethercard/tcpip.cpp \
../ethercard/udpserver.cpp \
../ethercard/webutil.cpp 

OBJS += \
./ethercard/EtherCard.o \
./ethercard/dhcp.o \
./ethercard/dns.o \
./ethercard/enc28j60.o \
./ethercard/tcpip.o \
./ethercard/udpserver.o \
./ethercard/webutil.o 

CPP_DEPS += \
./ethercard/EtherCard.d \
./ethercard/dhcp.d \
./ethercard/dns.d \
./ethercard/enc28j60.d \
./ethercard/tcpip.d \
./ethercard/udpserver.d \
./ethercard/webutil.d 


# Each subdirectory must supply rules for building sources it contributes
ethercard/%.o: ../ethercard/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


