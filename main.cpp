#include <avr/io.h>
#include <util/delay.h>

#define BAUD 19200
#define UBRR (F_CPU / 16 / BAUD - 1)

static void USART_Init() {
	/* Set baud rate */
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)UBRR;
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

static void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1 << UDRE0)))
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main() {
	USART_Init();
	DDRB |= 0b0010'0000;

	unsigned char data = '0';

	for (;;) {
		PORTB ^= PORTB5;
		_delay_ms(500);

		USART_Transmit(data);
		if (++data > '9') {
			data = '0';
		}
	}

	return 0;
}
