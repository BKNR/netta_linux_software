/*
* modbuswrapper.h & modbuswrapper.h:
* A C++ wrapper class for libmodbus. Creates the modbus tcp context and connects
* in the constructor, closes the connection and frees the modbus context in the
* destructor. Implements modbus_read_input_registers.
*
* Jari Leppänen 2015 for use with Pegasor Netta
*/

#include "modbuswrapper.h"
#include <string>
#include <cstdint>
#include <errno.h>
#include <stdexcept>
#include <cstring>
#include <array>

ModBusWrapper::ModBusWrapper(const char *ip, int port, int slave_id) {
	mb = modbus_new_tcp(ipstring, port); // creates the data structure for modbus	
	
	if (mb == NULL) {
		int errsv = errno;

		if (errvs == EINVAL) {
			throw std::invalid_argument("An invalid IP address was given");
		} else { 
			throw std::bad_alloc();
		}
	} else {
		if (modbus_set_slave(mb, slave_id) == 0) {
			if (modbus_connect(mb) == -1) {
				modbus_free(mb);

				int errsv = errno;
				char error [32];

				snprintf(error, 32, "Error: %d", errsv);
				throw std::runtime_error(error);
			}
		} else {
			int errsv = errno;
			modbus_free(mb);

			if (errsv == EINVAL) {
				throw std::invalid_argument("The slave number is invalid");
			} else {
				throw std::runtime_error("It failed, but no idea why");
			}
		}
	}
}

ModBusWrapper::~ModBusWrapper(void) {
	modbus_close(mb);
	modbus_free(mb);
}

void ModBusWrapper::readRegisters(int addr_of_first_reg, int num_regs, float *output_buffer) {
	
	uint16_t *buff16 = new uint16_t[num_regs+128];
	if (modbus_read_input_registers(mb, addr_of_first_reg, num_regs, buff16) != -1) {
		for (int i = 0; i < num_regs/2; i++) {
			output_buffer[i] = registerCombinator(buff16[2*i], buff16[2*i+1]);
		}
	} else {
		int errsv = errno;
		
		if (errsv == EMBMDATA) {
			throw std::runtime_error("Too many bits requested");
		} else if (errsv == EINVAL) {
			throw std::runtime_error("Got EINVAL even though it's not supposed to be possible");
		} else {
			throw std::runtime_error("Unknown error in reading the registers");
		}
	}
	delete[] buff16;
}

/*
* Combines the MSB and the LSB 16-bit register values into 
* a single 32-bit float.
*/
float ModBusWrapper::registerCombinator(uint16_t lsb, uint16_t msb) {
	uint32_t i;
	float f;

	i = (msb << 16) | lsb;
	memcpy(&f, &i, sizeof(f));

	return f;
}
