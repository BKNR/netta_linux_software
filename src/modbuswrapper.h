#ifndef T��_FILU_H_
#define T��_FILU_H_

#include se_oikee_modbus.h

/* HV t. Kikki-Hiiri */

class ModBusWrapper {
	public:
		ModBusWrapper(string, int, int)
		~ModBusWrapper();
		void readRegisters(int, int, *float);
	private:
		modbus_t *mb
}

#endif // T��_FILU_H_
