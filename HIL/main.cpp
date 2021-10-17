#include "uart.h"

int main() {
	uart::init(9600, 20, 20);
	uart::start();
	for (;;) {
		if (uart::available() > 0) {
			uint8_t data;
			uart::read(&data, 1);
			uart::write(&data, 1);
		}
	}
	return 0;
}
