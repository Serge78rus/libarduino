/*
 * bmp085.h
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

#ifndef BMP085_H_
#define BMP085_H_

#define BMP085_DEBUG 0

#define BMP085_I2CADDR 0x77

#define BMP085_ULTRALOWPOWER 0
#define BMP085_STANDARD      1
#define BMP085_HIGHRES       2
#define BMP085_ULTRAHIGHRES  3

class BMP085 {
public:
	BMP085() {}
	bool setup(uint8_t mode = BMP085_ULTRAHIGHRES);
	void update();
	int32_t getTemp() {return temp;} //in 1/10
	int32_t getPress() {return press;} //in Pa (1/100 hPa)
private:
  uint16_t readRawTemperature();
  uint32_t readRawPressure();
  int32_t computeB5(int32_t ut);
  uint8_t read8(uint8_t addr);
  uint16_t read16(uint8_t addr);
  void write8(uint8_t addr, uint8_t data);
	uint8_t oversampling;
  int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
  uint16_t ac4, ac5, ac6;
  int32_t temp, press;
};

#endif /* BMP085_H_ */
