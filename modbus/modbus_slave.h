/*
 * modbus_slave.h
 *
 *  Created on: 17 февр. 2015 г.
 *      Author: serge78rus
 */

#ifndef MODBUS_SLAVE_H_
#define MODBUS_SLAVE_H_

#define MB_S_BUFF_SIZE 64

class ModbusSlave {
public:
	ModbusSlave();
	void setup(uint8_t slaveId, uint8_t txPin,
			long baud, uint8_t format = SERIAL_8N2);
	void setupC(uint8_t cnt, bool (*read)(uint8_t addr),
			void (*write)(uint8_t addr, bool val));
	void setupDI(uint8_t cnt, bool (*read)(uint8_t addr));
	void setupHR(uint8_t cnt, uint16_t (*read)(uint8_t addr),
			void (*write)(uint8_t addr, uint16_t val));
	void setupIR(uint8_t cnt, uint16_t (*read)(uint8_t addr));
	void listen();
	uint16_t getErrCnt() {return errCnt;}
	void clearErrCnt() {errCnt = 0;}
private:
	void func1(uint16_t addr, uint16_t cnt);
	void func2(uint16_t addr, uint16_t cnt);
	void func3(uint16_t addr, uint16_t cnt);
	void func4(uint16_t addr, uint16_t cnt);
	void func5(uint16_t addr, uint16_t val);
	void func6(uint16_t addr, uint16_t val);
	void func15(uint16_t addr, uint16_t cnt, uint8_t len);
	void func16(uint16_t addr, uint16_t cnt, uint8_t len);
	uint16_t crc16(uint8_t len);
	void exception(uint8_t code);
	void send(uint8_t len);
	uint8_t txBit;
	volatile uint8_t *txReg;
	uint8_t id;
	uint8_t buff[MB_S_BUFF_SIZE];
	uint16_t t1_5;
	uint16_t errCnt;
	uint8_t cCnt;
	bool (*cRead)(uint8_t addr);
	void (*cWrite)(uint8_t addr, bool val);
	uint8_t diCnt;
	bool (*diRead)(uint8_t addr);
	uint8_t hrCnt;
	uint16_t (*hrRead)(uint8_t addr);
	void (*hrWrite)(uint8_t addr, uint16_t val);
	uint8_t irCnt;
	uint16_t (*irRead)(uint8_t addr);
};

extern ModbusSlave modbusSlave;

#endif /* MODBUS_SLAVE_H_ */
