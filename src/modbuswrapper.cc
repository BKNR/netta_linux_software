#include toi_toinen_filu.h

ModBusWrapper::ModBusWrapper(string ip, int port) {
	mb = modbus_new_tcp(ip, port);
	if (mb = NULL) {
		throw bad_alloc;
	}
}

ModBusWrapper::~ModBusWrapper(void) {
	modbus_close(mb);
	modbus_free(mb);
}

ModBusWrapper::readRegisters(int first_reg, int last_reg, float *buffer) {
	modbus_read_registers(mb, first_reg, las_reg, buffer)
}