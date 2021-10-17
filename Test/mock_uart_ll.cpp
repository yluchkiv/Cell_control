#include "uart_ll.h"

void uart_ll_init(size_t baud, ring_buffer* rx_buf, ring_buffer* tx_buf) {
	static_cast<void>(baud);
	static_cast<void>(rx_buf);
	static_cast<void>(tx_buf);
}

void uart_ll_start() {
	
}

void uart_ll_transmit(uint8_t data) {
	static_cast<void>(data);
}
