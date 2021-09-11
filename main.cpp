#include <avr/io.h>
#include <util/delay.h>

#define BAUD	19200
#define MYUBRR	F_CPU / 16 / BAUD - 1

static void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

static void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)))
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main()
{
	USART_Init(MYUBRR);
	DDRB |= 0b0010'0000;

	while (true) {
		PORTB ^= 0b0010'0000;
		_delay_ms(500);

		static unsigned char data = '0';
		USART_Transmit(data);
		if (++data > '9') {
			data = '0';
		}
	}

	return 0;
}

