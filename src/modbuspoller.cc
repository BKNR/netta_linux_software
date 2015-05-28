#include "modbuswrapper.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <unistd.h>
#include <cstring>

#define NUM_REGS 64
#define NETTA_IP "192.168.11.80"
#define NETTA_PORT 502
#define SLAVE_ID 10


int main(void) {

	ModBusWrapper *mbw;
	const char *ip = NETTA_IP;
	int port = NETTA_PORT;
	int slaveid = SLAVE_ID;
	int registers = NUM_REGS;

	try {
		mbw = new ModBusWrapper(ip, port, slaveid);
	} catch (std::exception &e) {
		std::cerr << e.what() << "\n";
		return -1;
	}

	float *value_buffer;
	int values = registers/2; // Registers have 16-bit data, values are 32-bit float

	value_buffer = new float[values];

	try {
		mbw->readRegisters(0, registers, value_buffer);
	} catch (std::exception &e) {
		std::cerr << e.what() << "\n";
		return -1;
	}

	char fname_buffer[64];
	memset(fname_buffer, 0, 64);
	readlink("/proc/self/exe", buffer, 64);

	// Take the filename out of the path

	string file_path(fname_buffer); 
	file_path.erase(file_path.end()-12, file_path.end())

	file_path += "measdata"
	std::ofstream f;
	f.open(file_path, std::ios::trunc);
	if (f.is_open()) {
		for (int i = 0; i < values; i++) {
			f << value_buffer[i] << "\n";
		}
		f.close();
	} else {
		std::cerr << "Unable to open file." << "\n";
	}

	delete mbw;
	
	return 0;
}
