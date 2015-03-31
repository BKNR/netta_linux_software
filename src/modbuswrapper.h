/*
* modbuswrapper.h & modbuswrapper.h:
* A C++ wrapper class for libmodbus. Creates the modbus tcp context and connects
* in the constructor, closes the connection and frees the modbus context in the
* destructor. Implements modbus_read_input_registers.
*
* Jari Leppänen 2015 for use with Pegasor Netta
*/

#ifndef MODBUSWRAPPER_H
#define MODBUSWRAPPER_H

#include <string>
#include <modbus.h>

class ModBusWrapper {
	public:
		ModBusWrapper(const char *ip, int port, int slave_id);
		~ModBusWrapper();
		void readRegisters(int addr_of_first_reg, int num_regs, float *buffer);
	private:
		float registerCombinator(uint16_t lsb, uint16_t msb);
		modbus_t *mb;
};

#endif // MODBUSWRAPPER_H
