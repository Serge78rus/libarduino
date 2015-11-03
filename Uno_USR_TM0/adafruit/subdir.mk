################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adafruit/glcdfont.c 

CPP_SRCS += \
../adafruit/Adafruit_BMP085.cpp \
../adafruit/Adafruit_GFX.cpp \
../adafruit/Adafruit_TFTLCD.cpp \
../adafruit/TouchScreen.cpp 

OBJS += \
./adafruit/Adafruit_BMP085.o \
./adafruit/Adafruit_GFX.o \
./adafruit/Adafruit_TFTLCD.o \
./adafruit/TouchScreen.o \
./adafruit/glcdfont.o 

C_DEPS += \
./adafruit/glcdfont.d 

CPP_DEPS += \
./adafruit/Adafruit_BMP085.d \
./adafruit/Adafruit_GFX.d \
./adafruit/Adafruit_TFTLCD.d \
./adafruit/TouchScreen.d 


# Each subdirectory must supply rules for building sources it contributes
adafruit/%.o: ../adafruit/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

adafruit/%.o: ../adafruit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/home/serge78rus/dev/avr/workspace/libarduino" -I"/home/serge78rus/dev/avr/workspace/libarduino/variants/standard" -DARDUINO=158 -DF_CPU=16000000L -DARDUINO_ARCH_AVR -DARDUINO_AVR_UNO -DUSR_TM0 -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


