#include toi_toinen_filu.h
#include <tarvittavat_libraryt>
#include <string>
#include <errno.h>
#include <system_error>

ModBusWrapper::ModBusWrapper(string ip, int port, int slave_id) {
	mb = modbus_new_tcp(ip.c_str(), port);
	if (mb = NULL) {
		int errsv = errno;
		if (errsv == EINVAL) {
			throw std::invalid_argument("An invalid IP address was given");
		} else { 
			throw std::bad_alloc("You done goofed son");
		}
	} else {
		if (modbus_set_slave(mb, slave_id)) {
			if (modbus_connect(mb) == -1) {
				modbus_free(mb);
				int errsv = errno;
				throw std::system_error(errsv, std::system_category()); // gives error form system
			}
		} else {
			int errsv = errno;
			modbus_free(mb);
			if (errsv == EINVAL) {
				throw std::invalid_argument("The slave number is invalid");
			} else {
				throw std::exception("It failed, but no idea why");
			}
		}
	}
}

ModBusWrapper::~ModBusWrapper(void) {
	modbus_close(mb);
	modbus_free(mb);
}

ModBusWrapper::readRegisters(int addr_of_first_reg, int num_regs, float *buffer) {
	uint16_t *buff16;
	buff16 = new uint16_t[num_regs];
	if (!modbus_read_input_registers(mb, first_reg, las_reg, buff16)) {
		int errsv = errno;
		if (errsv == EMBMDATA) {
			throw std::exception("Too many bits requested");
		} else {
			throw std::exception("Unknown error in reading the registers");
		}
	} else {
		//put buff16 in to the float buffer and check endianness
	}
	
	
	delete[] buff16;
}