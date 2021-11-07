#include <avr/io.h>
#include <util/delay.h>

#include "ring_buffer.h"
#include "scope_lock.h"
#include "sw_uart.h"
#include "uart.h"

int main() {
	uart::init(9600, 20, 20);
	uart::start();

	sw_uart::init(115200, &DDRB, &PORTB, PORTB5);

	unsigned char data = '0';
	ring_buffer buf(64);

	for (;;) {
		sw_uart::print("Hallo from sw uart\r\n");

		uart::print("Hello\r\n");
		uart::write(&data, 1);
		if (++data > '9') {
			data = '0';
		}

		buf.write(data);
	}

	return 0;
}
