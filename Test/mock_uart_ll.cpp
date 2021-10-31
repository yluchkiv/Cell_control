#include "uart_ll.h"

static ring_buffer *s_rx_buf{nullptr};
static ring_buffer *s_tx_buf{nullptr};

void uart_ll_init(uint32_t baud, ring_buffer *rx_buf, ring_buffer *tx_buf) {
	static_cast<void>(baud);
	s_rx_buf = rx_buf;
	s_tx_buf = tx_buf;
}

void uart_ll_start() {}

void uart_ll_transmit(uint8_t data) { static_cast<void>(data); }

uint8_t mock_uart_ll_tx_isr() {
	uint8_t b;
	s_tx_buf->read(b);
	return b;
}

void mock_uart_ll_rx_isr(uint8_t b) { s_rx_buf->write(b); }
