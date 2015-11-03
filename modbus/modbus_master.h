/*
 * modbus_master.h
 *
 *  Created on: 20 февр. 2015 г.
 *      Author: serge78rus
 */

#ifndef MODBUS_MASTER_H_
#define MODBUS_MASTER_H_

#define MB_M_BUFF_SIZE 64

class ModbusMaster {
public:
	enum Status {IDLE, PENDING, DONE, ERROR};
	ModbusMaster() {errCnt = 0; sts = IDLE;}
	void setup(uint8_t txPin, long baud, uint8_t format,
			uint16_t timeout);
	void execute(uint8_t slaveId, uint8_t func, uint16_t addr,
			uint8_t cnt, void *data);
	Status check();
	uint16_t getErrCnt() {return errCnt;}
	void clearErrCnt() {errCnt = 0;}
private:
	uint16_t crc16(uint8_t len);
	void send(uint8_t len);
	uint8_t txBit;
	volatile uint8_t *txReg;
	uint8_t buff[MB_M_BUFF_SIZE];
	uint16_t t1_5;
	uint16_t errCnt;
	uint16_t to;
	unsigned long timeout;
	Status sts;
	uint8_t id;
	uint8_t fn;
	union {
		void *res_v;
		uint8_t *res_u8;
		uint16_t *res_u16;
	};
	//uint16_t *res;
	uint8_t len;
};

extern ModbusMaster modbusMaster;

#endif /* MODBUS_MASTER_H_ */
