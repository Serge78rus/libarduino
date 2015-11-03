/*
 * modbus_slave.cpp
 *
 *  Created on: 17 февр. 2015 г.
 *      Author: serge78rus
 */

#include <Arduino.h>
#include <wiring_private.h>
#include <util/crc16.h>
#include <util/atomic.h>

#include "modbus_slave.h"

ModbusSlave modbusSlave;

static const uint8_t ILLEGAL_FUNCTION = 1;
static const uint8_t ILLEGAL_DATA_ADDRESS = 2;
static const uint8_t ILLEGAL_DATA_VALUE = 3;

ModbusSlave::ModbusSlave()
{
	cCnt = 0;
	diCnt = 0;
	hrCnt = 0;
	irCnt = 0;
	errCnt = 0;
}

void ModbusSlave::setup(uint8_t slaveId, uint8_t txPin,
		long baud, uint8_t format)
{
	id = slaveId;
	Serial.begin(baud, format);
  pinMode(txPin, OUTPUT);
  txBit = digitalPinToBitMask(txPin);
  txReg = portOutputRegister(digitalPinToPort(txPin));
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
	  *txReg &= ~txBit;
	}
	t1_5 = baud > 19200 ? 750 : 15000000 / baud;
}
void ModbusSlave::setupC(uint8_t cnt, bool (*read)(uint8_t addr),
		void (*write)(uint8_t addr, bool val))
{
	cCnt = cnt;
	cRead = read;
	cWrite = write;
}

void ModbusSlave::setupDI(uint8_t cnt, bool (*read)(uint8_t addr))
{
	diCnt = cnt;
	diRead = read;
}

void ModbusSlave::setupHR(uint8_t cnt, uint16_t (*read)(uint8_t addr),
		void (*write)(uint8_t addr, uint16_t val))
{
	hrCnt = cnt;
	hrRead = read;
	hrWrite = write;
}

void ModbusSlave::setupIR(uint8_t cnt, uint16_t (*read)(uint8_t addr))
{
	irCnt = cnt;
	irRead = read;
}

void ModbusSlave::listen()
{
	if (Serial.available()) {
		uint8_t ptr = 0;
		bool of = false;
		do {
			do {
				if (!of) {
					if (ptr < MB_S_BUFF_SIZE)
						buff[ptr++] = Serial.read();
					else
						of = true;
				} else
					Serial.read();
			} while (Serial.available());
			delayMicroseconds(t1_5);
		} while (Serial.available());
		if (!of && ptr > 7) {
			if (buff[0] == id || !buff[0]) {
				uint16_t crc = ((uint16_t(buff[ptr - 1]) << 8) | buff[ptr - 2]);
				if (crc16(ptr - 2) == crc) {
				  uint16_t addr = ((uint16_t(buff[2]) << 8) | buff[3]);
				  uint16_t b45 = ((uint16_t(buff[4]) << 8) | buff[5]);
				  switch (buff[1]) { //func
				  case 1: //read coils
				  	func1(addr, b45);
				  	break;
				  case 2: //read discrete inputs
				  	func2(addr, b45);
				  	break;
				  case 3: //read holding registers
				  	func3(addr, b45);
				  	break;
				  case 4: //read input registers
				  	func4(addr, b45);
				  	break;
				  case 5: //write single coil
				  	func5(addr, b45);
				  	break;
				  case 6: //write single register
				  	func6(addr, b45);
				  	break;
				  case 15: //write multiple coils
				  	func15(addr, b45, ptr);
				  	break;
				  case 16: //write multiple registers
				  	func16(addr, b45, ptr);
				  	break;
				  default:
					  exception(ILLEGAL_FUNCTION);
				  }
				} else
					++errCnt;
			}
		} else
			++errCnt;
	}
}

void ModbusSlave::func1(uint16_t addr, uint16_t cnt)
{
	if (buff[0]) { //no broadcast
		if (addr < cCnt) {
  		if (addr + cnt <= cCnt) {
  			buff[2] = cnt >> 3;//bytes cnt
  			if (cnt & 0x7)
  				++buff[2];
  			uint8_t ptr = 2;
  			for (uint8_t i = 0, bit; i < cnt; ++i) {
  				if (!(bit = (i & 0x7)))
  					buff[++ptr] = 0;
  				if (cRead(addr++))
  					buff[ptr] |= 1 << bit;
  			}
  			send(++ptr);
  		} else
  			exception(ILLEGAL_DATA_VALUE);
		} else
			exception(ILLEGAL_DATA_ADDRESS);
	}
}

void ModbusSlave::func2(uint16_t addr, uint16_t cnt)
{
	if (buff[0]) { //no broadcast
		if (addr < diCnt) {
  		if (addr + cnt <= diCnt) {
  			buff[2] = cnt >> 3;//bytes cnt
  			if (cnt & 0x7)
  				++buff[2];
  			uint8_t ptr = 2;
  			for (uint8_t i = 0, bit; i < cnt; ++i) {
  				if (!(bit = (i & 0x7)))
  					buff[++ptr] = 0;
  				if (diRead(addr++))
  					buff[ptr] |= 1 << bit;
  			}
  			send(++ptr);
  		} else
  			exception(ILLEGAL_DATA_VALUE);
		} else
			exception(ILLEGAL_DATA_ADDRESS);
	}
}

void ModbusSlave::func3(uint16_t addr, uint16_t cnt)
{
	if (buff[0]) { //no broadcast
		if (addr < hrCnt) {
  		if (addr + cnt <= hrCnt) {
  			buff[2] = cnt << 1;//bytes cnt
  			uint8_t ptr = 3;
  			uint16_t v;
  			for (uint8_t i = 0; i < cnt; ++i) {
  				v = hrRead(addr++);
				  buff[ptr++] = v >> 8;
				  buff[ptr++] = v & 0xff;
  			}
  			send(ptr);
  		} else
  			exception(ILLEGAL_DATA_VALUE);
		} else
			exception(ILLEGAL_DATA_ADDRESS);
	}
}

void ModbusSlave::func4(uint16_t addr, uint16_t cnt)
{
	if (buff[0]) { //no broadcast
		if (addr < irCnt) {
  		if (addr + cnt <= irCnt) {
  			buff[2] = cnt << 1;//bytes cnt
  			uint8_t ptr = 3;
  			uint16_t v;
  			for (uint8_t i = 0; i < cnt; ++i) {
  				v = irRead(addr++);
				  buff[ptr++] = v >> 8;
				  buff[ptr++] = v & 0xff;
  			}
  			send(ptr);
  		} else
  			exception(ILLEGAL_DATA_VALUE);
		} else
			exception(ILLEGAL_DATA_ADDRESS);
	}
}

void ModbusSlave::func5(uint16_t addr, uint16_t val)
{
	if (addr < cCnt) {
		if (val == 0 || val == 0xff00) {
			cWrite(addr, val);
			if (buff[0])
				send(6);
		} else
			exception(ILLEGAL_DATA_VALUE);
	} else
		exception(ILLEGAL_DATA_ADDRESS);
}

void ModbusSlave::func6(uint16_t addr, uint16_t val)
{
	if (addr < hrCnt) {
		hrWrite(addr, val);
		if (buff[0])
			send(6);
	} else
		exception(ILLEGAL_DATA_ADDRESS);
}

void ModbusSlave::func15(uint16_t addr, uint16_t cnt, uint8_t len)
{
  if (buff[6] == len - 9) {
		if (addr < cCnt) {
  		if (addr + cnt <= cCnt) {
  			uint8_t ptr = 6;
  			for (uint8_t i = 0, bit; i < cnt; ++i) {
  				if (!(bit = (i & 0x7)))
  					++ptr;
  				cWrite(addr++, (buff[ptr] >> bit) & 1);
  			}
  			if (buff[0])
  				send(6);
  		} else
  			exception(ILLEGAL_DATA_VALUE);
		} else
			exception(ILLEGAL_DATA_ADDRESS);
  } else
  	exception(ILLEGAL_DATA_VALUE);//????
}

void ModbusSlave::func16(uint16_t addr, uint16_t cnt, uint8_t len)
{
  if (buff[6] == len - 9) {
		if (addr < hrCnt) {
  		if (addr + cnt <= hrCnt) {
  			uint8_t ptr = 7;
  			uint16_t v;
  			for (uint8_t i = 0; i < cnt; ++i) {
  				v = uint16_t(buff[ptr++]) << 8;
  				hrWrite(addr++, v | buff[ptr++]);
  			}
  			if (buff[0])
  				send(6);
  		} else
  			exception(ILLEGAL_DATA_VALUE);
		} else
			exception(ILLEGAL_DATA_ADDRESS);
  } else
  	exception(ILLEGAL_DATA_VALUE);//????
}

uint16_t ModbusSlave::crc16(uint8_t len)
{
	uint16_t crc = 0xffff;
	for (uint8_t i = 0; i < len; ++i)
		crc = _crc16_update(crc, buff[i]);
	return crc;
}

void ModbusSlave::exception(uint8_t code)
{
	buff[1] |= 0x80;
	buff[2] = code;
	send(3);
}

void ModbusSlave::send(uint8_t len)
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
