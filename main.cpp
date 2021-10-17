#include <avr/io.h>
#include <util/delay.h>

#include "ring_buffer.h"
#include "scope_lock.h"
#include "uart.h"

class toggle {
      public:
	toggle() { PORTB ^= (1 << PORTB5); }
	~toggle() { PORTB ^= (1 << PORTB5); }
};

int main() {
	uart::init(9600, 20, 20);
	uart::start();
	DDRB |= 0b0010'0000;

	unsigned char data = '0';
	ring_buffer buf(64);

	for (;;) {
		toggle *tgl = new toggle();
		_delay_ms(500);
		delete tgl;
		_delay_ms(500);

		uart::print("Heello\r\n");
		uart::write(&data, 1);
		if (++data > '9') {
			data = '0';
		}

		buf.write(data);
	}

	return 0;
}
