/*
 * httpsrvr.h
 *
 *  Created on: 31 мая 2015 г.
 *      Author: serge78rus
 */

#ifndef HTTPSRVR_H_
#define HTTPSRVR_H_

//#define HTTP_TRACE

/*
 *
 * Connections
 *
 * 28j60		Arduino		DIP		REM
 * ______________________________________________
 *
 * GND			GND
 * VCC			+3.3						+3.3V
 * RST
 * CS				10 				16		defined by csPin param
 * SCK			13				19		SPI SCK
 * SI				11				17		SPI MOSI
 * SO				12				18		SPI MISO
 * WOL
 * INT
 * CLK
 *
 */

//#define HTTP_BUFF_SIZE 500
//#define HTTP_BUFF_SIZE 1000
#define HTTP_MAXPATH 20

#define PUTSTR(str) {memcpy(ptr, str, strlen(str)); ptr += strlen(str);}
#define PUTSTR_P(str) {memcpy_P(ptr, str, strlen(str)); ptr += strlen(str);}

class HTTPServer {
protected:
	HTTPServer() {}
public:
	bool setupDHCP(uint16_t buffSize, const uint8_t *macaddr, uint8_t csPin, const char *host);
	bool setupStat(uint16_t buffSize, const uint8_t *macaddr, uint8_t csPin, const uint8_t *ip,
			const uint8_t *gwIp = 0, const uint8_t *dnsIp = 0, const uint8_t *mask = 0);
	enum Method {
		UNKNOWN = 0,
		GET,
		POST
	};
	bool loop();
protected:
	virtual uint8_t findHandlerId(Method method, char *path) = 0;
	virtual uint16_t getContent(uint8_t hid, char *dst) = 0;
	virtual void parsePost(uint8_t hid, char *content) = 0;
private:
	char path[HTTP_MAXPATH + 1];
	char *ext;
};

#endif /* HTTPSRVR_H_ */
