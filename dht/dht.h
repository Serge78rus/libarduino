//
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.14
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
//

/*
 *
 * !!!!!!!!!!!!!!!!!!!!
 *
 * error in negative temp
 *
 * !!!!!!!!!!!!!!!!!!!!
 *
 */


#ifndef dht_h
#define dht_h

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#define DHT_LIB_VERSION "0.1.14"

#define DHTLIB_OK                0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#define DHTLIB_DHT11_WAKEUP     18
#define DHTLIB_DHT_WAKEUP       1

// max timeout is 100 usec.
// For a 16 Mhz proc 100 usec is 1600 clock cycles
// loops using DHTLIB_TIMEOUT use at least 4 clock cycli
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
#define DHTLIB_TIMEOUT (F_CPU/40000)

class DHT
{
public:
		DHT(uint8_t datapin, bool type_dht11 = false);
    // return values:
    // DHTLIB_OK
    // DHTLIB_ERROR_CHECKSUM
    // DHTLIB_ERROR_TIMEOUT
		int update() {return dht11 ? read11() : read();}

    inline int16_t getTemp() {return temp;}
    inline int8_t getTempI() {return temp / 10;}
    inline int8_t getTempF() {return temp % 10;}
    inline int16_t getRH() {return rh;}
    inline int8_t getRHI() {return rh / 10;}
    inline int8_t getRHF() {return rh % 10;}


private:
    int read11();
    int read();
    int _readSensor(uint8_t wakeupDelay);
    uint8_t bits[5];  // buffer to receive data
    int16_t temp, rh;
    const uint8_t pin;
    const bool dht11;
};
#endif
//
// END OF FILE
//
