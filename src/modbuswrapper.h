#ifndef TÄÄ_FILU_H_
#define TÄÄ_FILU_H_

#include se_oikee_modbus.h

class ModBusWrapper {
	public:
		ModBusWrapper(string, int, int)
		~ModBusWrapper();
		void readRegisters(int, int, *float);
	private:
		modbus_t *mb
}

#endif // TÄÄ_FILU_H_