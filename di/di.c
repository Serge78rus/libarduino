/*
 * di.c
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: serge78rus
 */

#include "Arduino.h"
#include "di.h"

#if F_CPU == 16000000L
#define DI_CYCLES 20
#elif F_CPU == 8000000L
#define DI_CYCLES 10
#else
#error Invalid F_CPU!
#endif

static uint8_t num;
static uint8_t idx;
static uint8_t cnt = DI_CYCLES;
static uint8_t *values;
static volatile uint16_t value = 0;
typedef struct {
	uint8_t bit;
	uint8_t port;
} DIPin;
DIPin *pins;

#if defined USR_TM0
void di_setup(const uint8_t *pinarr, uint8_t pinnum, bool ext_timer)
#else
void di_setup(const uint8_t *pinarr, uint8_t pinnum)
#endif
{
	idx = num = pinnum;
	values = (uint8_t*)malloc(num);
	pins = (DIPin*)malloc(num * sizeof(DIPin));
	for (int i = 0; i < num; ++i) {
		pinMode(pinarr[i], INPUT_PULLUP);
		values[i] = 0;
		pins[i].bit = digitalPinToBitMask(pinarr[i]);
		pins[i].port = digitalPinToPort(pinarr[i]);
	}
	for (int i = 0; i < num; ++i)
		if (*portInputRegister(pins[i].port) & pins[i].bit)
			value |= 1 << i;
#if defined USR_TM0
	if (!ext_timer) {
		uint8_t oldSREG = SREG;
		cli();
		user_timer0_func = &di_update;
		SREG = oldSREG;
	}
#endif
}

uint16_t di_get()
{
	uint16_t val;
	uint8_t oldSREG = SREG;
	cli();
	val = value;
	SREG = oldSREG;
	return val;
}

void di_update()
{
	--idx;
	if (*portInputRegister(pins[idx].port) & pins[idx].bit)
		++values[idx];
	if (!idx) {
		idx = num;
		if (!--cnt) {
			cnt = DI_CYCLES;
			value = 0;
			for (int i = 0; i < num; ++i) {
				if (values[i] > DI_CYCLES / 2)
					value |= 1 << i;
				values[i] = 0;
			}
		}
	}
}

