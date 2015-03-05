#include "modbuswrapper.h"
#include <string>
#include <cstdint>
#include <errno.h>
#include <stdexcept>


ModBusWrapper::ModBusWrapper(std::string ip, int port, int slave_id) {
	const char* ipstring = ip.c_str();
	modbus_t *mb;
	
	mb = modbus_new_tcp(ipstring, port);
	
	if (mb == NULL) {
		int errsv = errno;

		if (errsv == EINVAL) {
			throw std::invalid_argument("An invalid IP address was given");
		} else { 
			throw std::bad_alloc();
		}
	} else {
		if (modbus_set_slave(mb, slave_id)) {
			if (modbus_connect(mb) == -1) {
				modbus_free(mb);

				int errsv = errno;
				std::string error;

				snprintf(error, 32, "Error: %d", errsv);
				throw std::runtime_error(error);
			}
		} else {
			int errsv = ernrso;
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
	uint16_t *buff16;
	buff16 = new uint16_t[num_regs];
	if (modbus_read_input_registers(mb, addr_of_first_reg, num_regs, buff16)) {
		for (int i = 0; i < num_regs/2; i++) {
			output_buffer[i] = register_combinator(buff16[2*i], buff16[2*i+1]);
		}
	} else {
		int errsv = errno;
		
		if (errsv == EMBMDATA) {
			throw std::runtime_error("Too many bits requested");
		} else {
			throw std::runtime_error("Unknown error in reading the registers");
		}

	}
	
	delete[] buff16;
}

float register_combinator(uint16_t lsb, uint16_t msb) {
	uint32_t i;
	float f;

	i = (msb << 16) | lsb;
	memcpy(&f, &i, sizeof(f));

	return f;
}
