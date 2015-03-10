#ifndef MODBUSWRAPPER_H
#define MODBUSWRAPPER_H

#include <string>
#include <modbus.h>

class ModBusWrapper {
	public:
		ModBusWrapper(std::string ip, int port, int slave_id);
		~ModBusWrapper();
		void readRegisters(int addr_of_first_reg, int num_regs, float *buffer);
	private:
		float registerCombinator(uint16_t lsb, uint16_t msb);
		modbus_t *mb;
};

#endif // MODBUSWRAPPER_H
