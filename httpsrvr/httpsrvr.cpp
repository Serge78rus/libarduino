/*
 * httpsrvr.cpp
 *
 *  Created on: 31 мая 2015 г.
 *      Author: serge78rus
 */

#include <Arduino.h>
#include <ethercard/EtherCard.h>

#include "httpsrvr.h"

//byte Ethernet::buffer[HTTP_BUFF_SIZE]; // tcp/ip send and receive buffer

#ifdef HTTP_TRACE
#define HTTP_TRACE_MSG(msg) Serial.println(msg);
#define HTTP_TRACE_VAL(name, val) { Serial.print(name); Serial.print(": "); \
		Serial.println(val); }
#define HTTP_TRACE_ERR(msg) Serial.println("ERROR: "msg);
#define HTTP_TRACE_STS() { ether.printIp("MYIP: ", ether.myip); \
		ether.printIp("NETMASK: ", ether.netmask); \
		ether.printIp("BROADCASTIP: ", ether.broadcastip); \
		ether.printIp("GWIP: ", ether.gwip); \
		ether.printIp("DHCPIP: ", ether.dhcpip); \
		ether.printIp("DNSIP: ", ether.dnsip); }
#else
#define HTTP_TRACE_MSG(msg) ;
#define HTTP_TRACE_VAL(name, val) ;
#define HTTP_TRACE_ERR(msg) ;
#define HTTP_TRACE_STS() ;
#endif

static const char HEADER_1[] PROGMEM =
		"HTTP/1.0 ";
static const char HEADER_2[] PROGMEM =
		"\r\n";
static const char HEADER_3_HTML[] PROGMEM =
		"Content-Type: text/html\r\n";
static const char HEADER_3_CSS[] PROGMEM =
		"Content-Type: text/css\r\n";
static const char HEADER_3_TXT[] PROGMEM =
		"Content-Type: text/plain\r\n";
static const char HEADER_3_JS[] PROGMEM =
		"Content-Type: application/x-javascript\r\n";
static const char HEADER_3_JSON[] PROGMEM =
		"Content-Type: application/json\r\n";
static const char HEADER_4[] PROGMEM =
		"Server: AVR httpserver\r\n"
		"\r\n";

static const char CODE_200[] PROGMEM = "200 OK";
static const char CODE_404[] PROGMEM = "404 Not Found";
static const char CODE_405[] PROGMEM = "405 Not Allowed";

static const char ERROR_1[] PROGMEM =
		"<html>"
		"<head><title>";
static const char ERROR_2[] PROGMEM =
		"</title></head>"
		"<body bgcolor='white'>"
		"<center><h1>";
static const char ERROR_3[] PROGMEM =
		"</h1></center>"
		"<hr><center>AVR httpserver</center>"
		"</body>"
		"</html>";

#define PUTERROR_P(code) { PUTSTR_P(HEADER_1) PUTSTR_P(code) PUTSTR_P(HEADER_2) \
		PUTSTR_P(HEADER_3_HTML) PUTSTR_P(HEADER_4) PUTSTR_P(ERROR_1) PUTSTR_P(code) \
		PUTSTR_P(ERROR_2) PUTSTR_P(code) PUTSTR_P(ERROR_3) }
#define PUTHEADER_200_HTML() { PUTSTR_P(HEADER_1) PUTSTR_P(CODE_200) PUTSTR_P(HEADER_2) \
		PUTSTR_P(HEADER_3_HTML) PUTSTR_P(HEADER_4)}
#define PUTHEADER_200_CSS() { PUTSTR_P(HEADER_1) PUTSTR_P(CODE_200) PUTSTR_P(HEADER_2) \
		PUTSTR_P(HEADER_3_CSS) PUTSTR_P(HEADER_4)}
#define PUTHEADER_200_TXT() { PUTSTR_P(HEADER_1) PUTSTR_P(CODE_200) PUTSTR_P(HEADER_2) \
		PUTSTR_P(HEADER_3_TXT) PUTSTR_P(HEADER_4)}
#define PUTHEADER_200_JS() { PUTSTR_P(HEADER_1) PUTSTR_P(CODE_200) PUTSTR_P(HEADER_2) \
		PUTSTR_P(HEADER_3_JS) PUTSTR_P(HEADER_4)}
#define PUTHEADER_200_JSON() { PUTSTR_P(HEADER_1) PUTSTR_P(CODE_200) PUTSTR_P(HEADER_2) \
		PUTSTR_P(HEADER_3_JSON) PUTSTR_P(HEADER_4)}

bool HTTPServer::setupDHCP(uint16_t buffSize, const uint8_t *macaddr, uint8_t csPin,
		const char *host)
{
  if (ether.begin(buffSize, macaddr, csPin)) {
	  if (ether.dhcpSetup(host)) {
	  	HTTP_TRACE_STS()
	  	return true;
	  } else {
	  	HTTP_TRACE_ERR("ether.dhcpSetup()")
	  	return false;
	  }
  } else {
  	HTTP_TRACE_ERR("ether.begin()")
  	return false;
  }
}

bool HTTPServer::setupStat(uint16_t buffSize, const uint8_t *macaddr, uint8_t csPin,
		const uint8_t *ip, const uint8_t *gwIp, const uint8_t *dnsIp, const uint8_t *mask)
{
  if (ether.begin(buffSize, macaddr, csPin)) {
 	  if (ether.staticSetup(ip, gwIp, dnsIp, mask)) {
	  	HTTP_TRACE_STS()
 	  	return true;
 	  } else {
	  	HTTP_TRACE_ERR("ether.staticSetup()")
	  	return false;
 	  }
  } else {
  	HTTP_TRACE_ERR("ether.begin()")
  	return false;
  }
}

bool HTTPServer::loop()
{
	uint16_t rl = ether.packetReceive();
	if (rl) {
		HTTP_TRACE_VAL("rl", rl)
		uint16_t pl = ether.packetLoop(rl);
		if (pl) {
			HTTP_TRACE_VAL("pl", pl)
			HTTP_TRACE_VAL("buff", (char*)(Ethernet::buffer + pl))
	  	Method rt = UNKNOWN;
	  	char *psp = (char*)Ethernet::buffer + pl, *pdp = path;
	  	if (!strncmp(psp, "GET", 3)) {
	  		rt = GET;
	  		psp += 4;
	  		HTTP_TRACE_MSG("GET")
	  	} else if (!strncmp(psp, "POST", 4)) {
	  		rt = POST;
	  		psp += 5;
	  		HTTP_TRACE_MSG("POST")
	  	}
	  	else
	  		HTTP_TRACE_ERR("Unknown req type")
			uint8_t *ptr = ether.tcpOffset();
			bool ret;
	  	if (rt) {
	  		ext = 0;
	  		for (uint8_t cnt = 0;;) {
	  			if (*psp != ' ' && cnt++ < HTTP_MAXPATH) {
	  				if (*psp == '.')
	  					ext = pdp;
	  				*pdp++ = *psp++;
	  			} else {
	  				*pdp = 0;
	  				if (!ext)
	  					ext = pdp;
	  				break;
	  			}
	  		}
	  		HTTP_TRACE_VAL("path", path)
	  		HTTP_TRACE_VAL("ext", ext)
	  		uint8_t hid = findHandlerId(rt, path);
	  		if (hid) {
	  			switch (rt) {
	  				case POST:
				  		for (uint8_t cnt = 0; cnt < 4;) {
				  			if (*psp == '\r' || *psp == '\n')
				  				++cnt;
				  			else
				  				cnt = 0;
				  			++psp;
				  		}
				  		HTTP_TRACE_VAL("post", psp)
	  					parsePost(hid, psp);
				  		/*no break*/
	  				case GET:
	  					if (!strcmp(ext, ".css"))
		  					PUTHEADER_200_CSS()
	  					else if (!strcmp(ext, ".txt"))
		  					PUTHEADER_200_TXT()
	  					else if (!strcmp(ext, ".js"))
		  					PUTHEADER_200_JS()
	  					else if (!strcmp(ext, ".json"))
		  					PUTHEADER_200_JSON()
	  					else
	  						PUTHEADER_200_HTML()
					  	ptr += getContent(hid, (char*)ptr);
					  	break;
			  		default:
			  			;
		  		}
	  		} else
	  			PUTERROR_P(CODE_404)
	  		ret = true;
	  	} else {
  			PUTERROR_P(CODE_405)
	  		ret = false;
	  	}
	    ether.httpServerReply(ptr - ether.tcpOffset());
	  	return ret;
		} else
			return false;
	} else
		return false;
}

