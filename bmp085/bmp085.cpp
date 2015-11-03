/*
 * bmp085.cpp
 *
 *  Created on: 17 июля 2015 г.
 *      Author: serge78rus
 *
 *  Based on Adafruit BMP085/BMP180 Barometric Pressure + Temp sensor library
 *  (see banner bellow)
 *
 *  BSD license
 */

/***************************************************
  This is a library for the Adafruit BMP085/BMP180 Barometric Pressure + Temp sensor

  Designed specifically to work with the Adafruit BMP085 or BMP180 Breakout
  ----> http://www.adafruit.com/products/391
  ----> http://www.adafruit.com/products/1603

  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Arduino.h>
#include <wire/Wire.h>

#include "bmp085.h"

#define BMP085_CAL_AC1           0xAA  // R   Calibration data (16 bits)
#define BMP085_CAL_AC2           0xAC  // R   Calibration data (16 bits)
#define BMP085_CAL_AC3           0xAE  // R   Calibration data (16 bits)
#define BMP085_CAL_AC4           0xB0  // R   Calibration data (16 bits)
#define BMP085_CAL_AC5           0xB2  // R   Calibration data (16 bits)
#define BMP085_CAL_AC6           0xB4  // R   Calibration data (16 bits)
#define BMP085_CAL_B1            0xB6  // R   Calibration data (16 bits)
#define BMP085_CAL_B2            0xB8  // R   Calibration data (16 bits)
#define BMP085_CAL_MB            0xBA  // R   Calibration data (16 bits)
#define BMP085_CAL_MC            0xBC  // R   Calibration data (16 bits)
#define BMP085_CAL_MD            0xBE  // R   Calibration data (16 bits)

#define BMP085_CONTROL           0xF4
#define BMP085_TEMPDATA          0xF6
#define BMP085_PRESSUREDATA      0xF6
#define BMP085_READTEMPCMD       0x2E
#define BMP085_READPRESSURECMD   0x34

bool BMP085::setup(uint8_t mode)
{
  oversampling = mode;
  Wire.begin();
  if (read8(0xD0) != 0x55)
  	return false;
  /* read calibration data */
  ac1 = read16(BMP085_CAL_AC1);
  ac2 = read16(BMP085_CAL_AC2);
  ac3 = read16(BMP085_CAL_AC3);
  ac4 = read16(BMP085_CAL_AC4);
  ac5 = read16(BMP085_CAL_AC5);
  ac6 = read16(BMP085_CAL_AC6);
  b1 = read16(BMP085_CAL_B1);
  b2 = read16(BMP085_CAL_B2);
  mb = read16(BMP085_CAL_MB);
  mc = read16(BMP085_CAL_MC);
  md = read16(BMP085_CAL_MD);
#if (BMP085_DEBUG == 1)
  Serial.print("ac1 = "); Serial.println(ac1, DEC);
  Serial.print("ac2 = "); Serial.println(ac2, DEC);
  Serial.print("ac3 = "); Serial.println(ac3, DEC);
  Serial.print("ac4 = "); Serial.println(ac4, DEC);
  Serial.print("ac5 = "); Serial.println(ac5, DEC);
  Serial.print("ac6 = "); Serial.println(ac6, DEC);
  Serial.print("b1 = "); Serial.println(b1, DEC);
  Serial.print("b2 = "); Serial.println(b2, DEC);
  Serial.print("mb = "); Serial.println(mb, DEC);
  Serial.print("mc = "); Serial.println(mc, DEC);
  Serial.print("md = "); Serial.println(md, DEC);
#endif
  return true;
}

void BMP085::update()
{
  int32_t ut = readRawTemperature();
  int32_t up = readRawPressure();
  int32_t b5 = computeB5(ut);
  temp = (b5 + 8) >> 4;
  int32_t b6 = b5 - 4000;
  int32_t x1 = ((int32_t)b2 * ((b6 * b6) >> 12 )) >> 11;
  int32_t x2 = ((int32_t)ac2 * b6) >> 11;
  int32_t x3 = x1 + x2;
  int32_t b3 = ((((int32_t)ac1 * 4 + x3) << oversampling) + 2) / 4;
  x1 = ((int32_t)ac3 * b6) >> 13;
  x2 = ((int32_t)b1 * ((b6 * b6) >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  uint32_t b4 = ((uint32_t)ac4 * (uint32_t)(x3 + 32768)) >> 15;
  uint32_t b7 = ((uint32_t)up - b3) * (uint32_t)( 50000UL >> oversampling );
  press = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  x1 = (press >> 8) * (press >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * press) >> 16;
  press = press + ((x1 + x2 + (int32_t)3791) >> 4);
#if BMP085_DEBUG == 1
  Serial.print("t = "); Serial.println(temp);
  Serial.print("p = "); Serial.println(press);
#endif
}

uint16_t BMP085::readRawTemperature() {
  write8(BMP085_CONTROL, BMP085_READTEMPCMD);
  delay(5);
#if BMP085_DEBUG == 1
  Serial.print("Raw temp: "); Serial.println(read16(BMP085_TEMPDATA));
#endif
  return read16(BMP085_TEMPDATA);
}

uint32_t BMP085::readRawPressure() {
  uint32_t raw;
  write8(BMP085_CONTROL, BMP085_READPRESSURECMD + (oversampling << 6));
  switch (oversampling) {
  	case BMP085_ULTRALOWPOWER:
  		delay(5);
  		break;
  	case BMP085_STANDARD:
  		delay(8);
  		break;
  	case BMP085_HIGHRES:
  		delay(14);
  		break;
  	default:
  		delay(26);
  }
  raw = read16(BMP085_PRESSUREDATA);
  if (oversampling) {
  	raw <<= 8;
  	raw |= read8(BMP085_PRESSUREDATA+2);
  	raw >>= (8 - oversampling);
  }
#if BMP085_DEBUG == 1
  Serial.print("Raw pressure: "); Serial.println(raw);
#endif
  return raw;
}

int32_t BMP085::computeB5(int32_t ut)
{
  int32_t x1 = (ut - (int32_t)ac6) * ((int32_t)ac5) >> 15;
  int32_t x2 = ((int32_t)mc << 11) / (x1+(int32_t)md);
  return x1 + x2;
}

uint8_t BMP085::read8(uint8_t addr)
{
  uint8_t ret;
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device
  Wire.write(addr); // sends register address to read from
  Wire.endTransmission(); // end transmission
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device
  Wire.requestFrom(BMP085_I2CADDR, 1);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  Wire.endTransmission(); // end transmission
  return ret;
}

uint16_t BMP085::read16(uint8_t addr)
{
  uint16_t ret;
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device
  Wire.write(addr); // sends register address to read from
  Wire.endTransmission(); // end transmission
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device
  Wire.requestFrom(BMP085_I2CADDR, 2);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret <<= 8;
  ret |= Wire.read(); // receive DATA
  Wire.endTransmission(); // end transmission
  return ret;
}

void BMP085::write8(uint8_t addr, uint8_t data)
{
  Wire.beginTransmission(BMP085_I2CADDR); // start transmission to device
  Wire.write(addr); // sends register address to read from
  Wire.write(data);  // write data
  Wire.endTransmission(); // end transmission
}
