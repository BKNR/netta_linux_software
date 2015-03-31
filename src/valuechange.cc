#include "modbuswrapper.h"

#include <iostream>
#include <ctime>
#include <exception>

#define NUM_REGS 64
#define NETTA_IP "196.168.11.80"
#define NETTA_PORT 502
#define SLAVE_ID 10

/* Vaikuttaa aika usein loppuvan virheeseen. (10.3.2015 -Pasi)*/

int main(void) {

	ModBusWrapper *mbw;
	
	try {
		mbw = new ModBusWrapper(NETTA_IP, NETTA_PORT, SLAVE_ID);
	} catch (std::exception &e) {
		std::cerr << e.what() << "\n";
		return -1;
	}


	float *value_buffer;
	float humidity;
	int change, first;

	change = 0;
	first = 1;

	std::time_t first_time, second_time;
	std::cout.precision(12);
	while (change != 2) {
		value_buffer = new float[1];

		try {
			mbw->readRegisters(34, 2, value_buffer);
		} catch (std::exception &e) {
			std::cerr << e.what() << "\n";
			return -1;
		}

		if (first) {
			humidity = value_buffer[0];
			first = 0;
		}

		if (humidity != value_buffer[0]) {
			change++;
			if (change == 1) {
				first_time = std::time(0);
			} else if (change == 2) {
				second_time = std::time(0);
			}
			humidity = value_buffer[0];
			std::cout << humidity << "\n";
		}

		std::cout << humidity << "\n";

		delete[] value_buffer;
	}

	std::time_t result = second_time - first_time;

	std::cout << result << "\n";

	delete mbw;
	
	return 0;
}
