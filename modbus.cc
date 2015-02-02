

class ModBus {
	public:
		Modbus(string, int)
		~Modbus();
		void readRegisters(int, int, *float);
	private:
		modbus_t *mb
}

Modbus::Modbus(string ip, int port) {
	mb = modbus_new_tcp(ip, port);
}

Modbus::~Modbus(void) {
	modbus_close(mb);
	modbus_free(mb);
}

Modbus::readRegisters(int first_reg, int last_reg, float *buffer) {
	modbus_read_registers(mb, first_reg, las_reg, buffer)
}