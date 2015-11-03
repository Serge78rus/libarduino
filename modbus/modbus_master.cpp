/*
 * modbus_master.cpp
 *
 *  Created on: 20 февр. 2015 г.
 *      Author: serge78rus
 */

#include <Arduino.h>
#include <wiring_private.h>
#include <util/crc16.h>
#include <util/atomic.h>

#include "modbus_master.h"

ModbusMaster modbusMaster;

void ModbusMaster::setup(uint8_t txPin, long baud, uint8_t format,
		uint16_t timeout)
{
	Serial.begin(baud, format);
  pinMode(txPin, OUTPUT);
  txBit = digitalPinToBitMask(txPin);
  txReg = portOutputRegister(digitalPinToPort(txPin));
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
	  *txReg &= ~txBit;
	}
	t1_5 = baud > 19200 ? 750 : 15000000 / baud;
	to = timeout;
	sts = IDLE;
}

void ModbusMaster::execute(uint8_t slaveId, uint8_t func, uint16_t addr,
		uint8_t cnt, void *data)
{
	uint8_t ptr = 0;
	buff[ptr++] = id = slaveId;
	buff[ptr++] = fn = func;
	buff[ptr++] = addr >> 8;
	buff[ptr++] = addr & 0xff;
	buff[ptr++] = 0;
	buff[ptr++] = len = cnt;
	res_v = data;
	send(ptr);
	if (slaveId) {
		timeout = millis() + to;
		sts = PENDING;
	} else
		sts = DONE;
}

ModbusMaster::Status ModbusMaster::check()
{
	if (Serial.available()) {
		uint8_t ptr = 0;
		bool of = false;
		do {
			do {
				if (!of) {
					if (ptr < MB_M_BUFF_SIZE)
						buff[ptr++] = Serial.read();
					else
						of = true;
				} else
					Serial.read();
			} while (Serial.available());
			delayMicroseconds(t1_5);
		} while (Serial.available());
		if (!of && ptr > 5 && sts == PENDING) {
			uint16_t crc = ((uint16_t(buff[ptr - 1]) << 8) | buff[ptr - 2]);
			if (crc16(ptr - 2) == crc && buff[0] == id && buff[1] == fn) {
				switch (fn) {
				case 1: //read coils
				case 2: //read discrete inputs
					if (len & 0x7)
						len = (len >> 3) + 1;
					else
						len >>= 3;
					if (buff[2] == len && ptr == 5 + len) {
						memcpy(res_v, buff + 3, len);
						sts = DONE;
					}
					break;
				case 3: //read holding registers
				case 4: //read input registers
					if (buff[2] == len << 1 && ptr == 5 + buff[2]) {
						for (uint8_t i = 0, *p = buff + 2; i < len; ++i) {
							uint16_t hi = *(++p);
							res_u16[i] = (hi << 8) | *(++p);
						}
						sts = DONE;
					}
					break;
				}
			}
		}
	}
	if (sts == PENDING && millis() > timeout)
		sts = ERROR;
	return sts;
}

uint16_t ModbusMaster::crc16(uint8_t len)
{
	uint16_t crc = 0xffff;
	for (uint8_t i = 0; i < len; ++i)
		crc = _crc16_update(crc, buff[i]);
	return crc;
}

void ModbusMaster::send(uint8_t len)
{
	uint16_t crc = crc16(len);
  buff[len++] = crc & 0xff;
  buff[len++] = crc >> 8;
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		cbi(UCSR0B, RXEN0);
	}
	while (Serial.available())
		Serial.read();
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		*txReg |= txBit;
	}
	for (uint8_t i = 0; i < len; ++i)
    Serial.write(buff[i]);
	Serial.flush();
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		*txReg &= ~txBit;
		sbi(UCSR0B, RXEN0);
	}
}

