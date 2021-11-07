#include "uart.h"
#include "sw_uart.h"

#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

int main() {
	uart::init(9600, 20, 20);
	uart::start();

	sw_uart::init(115200, &DDRB, &PORTB, 5);

	for (;;) {
		if (uart::available() > 0) {
			uint8_t data;
			uart::read(&data, 1);
			uart::write(&data, 1);
		}
		_delay_ms(2000);
		sw_uart::print("swuart\r\n");
	}
	return 0;
}

static_assert(sizeof(size_t) == 2, "Size is not correct");
