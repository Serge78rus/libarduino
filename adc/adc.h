/*
 * adc.h
 *
 *  Created on: 13 февр. 2015 г.
 *      Author: serge78rus
 */

#ifndef ADC_H_
#define ADC_H_

/*
ADC reference:
DEFAULT: the default analog reference of 5 volts (on 5V Arduino boards)
		or 3.3 volts (on 3.3V Arduino boards)
INTERNAL: an built-in reference, equal to 1.1 volts on the ATmega168
		or ATmega328 and 2.56 volts on the ATmega8 (not available on the Arduino Mega)
INTERNAL1V1: a built-in 1.1V reference (Arduino Mega only)
INTERNAL2V56: a built-in 2.56V reference (Arduino Mega only)
EXTERNAL: the voltage applied to the AREF pin (0 to 5V only) is used
		as the reference.
*/

#define ADC_REF_AREF EXTERNAL
#define ADC_REF_AVCC DEFAULT
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || \
	defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || \
	defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define ADC_REF_1V1 INTERNAL1V1
#define ADC_REF_2V56 INTERNAL2V56
#else
#define ADC_REF_1V1 INTERNAL
#endif

#define ADC_CHAN_NUM 11

#ifdef __cplusplus
extern "C"{
#endif

#if defined USR_TM0
void adc_setup(uint8_t ref, bool ext_timer);
#else
void adc_setup(uint8_t ref);
#endif
uint16_t adc_get(uint8_t chan);
void adc_update();
void adc_start();
uint8_t adc_ready();

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* ADC_H_ */
