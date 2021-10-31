#include "string.h"
#include <stdlib.h>

#include "ring_buffer.h"
#include "scope_lock.h"
#include "uart.h"
#include "uart_ll.h"

static ring_buffer *tx_buf = nullptr;
static ring_buffer *rx_buf = nullptr;

bool uart::initialized_{false};
size_t uart::tx_size_{};
size_t uart::rx_size_{};

bool uart::init(uint32_t baud, size_t tx_size, size_t rx_size) {
	if (initialized_) {
		return false;
	}
	tx_size_ = tx_size;
	rx_size_ = rx_size;
	tx_buf = new ring_buffer(tx_size);
	rx_buf = new ring_buffer(rx_size);
	::uart_ll_init(baud, rx_buf, tx_buf);
	initialized_ = true;
	return true;
}

void uart::start() { ::uart_ll_start(); }

size_t uart::available() {
	scope_lock sl{};
	size_t avail = rx_buf->count();
	return avail;
}

bool uart::print(const char *str) {
	size_t len = strlen(str);
	return uart::write(reinterpret_cast<const uint8_t *>(str), len);
}

bool uart::write(const uint8_t *data, size_t size) {
	scope_lock sl{};
	bool empty = tx_buf->count() == 0;
	if (size >= (tx_size_ - tx_buf->count())) {
		return false;
	}
	for (size_t i = 0; i < size; i++) {
		tx_buf->write(data[i]);
	}
	if (empty && (tx_buf->count() > 0)) {
		uint8_t b;
		tx_buf->read(b);
		::uart_ll_transmit(b);
	}
	return true;
}

size_t uart::read(uint8_t *data, size_t size) {
	scope_lock sl{};
	size_t count = size;
	if (count > rx_buf->count()) {
		count = rx_buf->count();
	}
	for (size_t i = 0; i < count; i++) {
		rx_buf->read(data[i]);
	}
	return count;
}
