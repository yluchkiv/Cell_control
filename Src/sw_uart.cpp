#include <string.h>
#include <util/delay.h>

#include "scope_lock.h"
#include "sw_uart.h"

uint32_t sw_uart::baud_{0};
volatile uint8_t *sw_uart::ddr_{nullptr};
volatile uint8_t *sw_uart::port_{nullptr};
uint8_t sw_uart::pin_{0};

void sw_uart::init(uint32_t baud, volatile uint8_t *ddr, volatile uint8_t *port,
		   uint8_t pin) {
	baud_ = baud;
	ddr_ = ddr;
	port_ = port;
	pin_ = pin;

	*ddr_ |= static_cast<uint8_t>(1 << pin_);  /* Enable GPIO output */
	*port_ |= static_cast<uint8_t>(1 << pin_); /* Set GPIO output high */
}

void sw_uart::print(const char *str) {
	sw_uart::write(reinterpret_cast<const uint8_t *>(str), ::strlen(str));
}

void sw_uart::write(const uint8_t *data, size_t size) {
	const uint16_t bit_delay = ((F_CPU / baud_) / 4) - (15 / 4);
	const uint8_t reg_mask = static_cast<uint8_t>(1 << pin_);
	const uint8_t inv_mask = static_cast<uint8_t>(~(1 << pin_));

	for (size_t i = 0; i < size; i++) {
		scope_lock sl{};

		/* start bit */
		*port_ &= inv_mask;
		_delay_loop_2(bit_delay);

		uint8_t b = data[i];
		/* each of the 8 bits */
		for (uint8_t bit = 8; bit > 0; bit--) {
			if (b & 1) {
				*port_ |= reg_mask;
			} else {
				*port_ &= inv_mask;
			}
			b >>= 1;
			_delay_loop_2(bit_delay);
		}

		/* 2 stop bits */
		*port_ |= reg_mask;
		_delay_loop_2(bit_delay);
		_delay_loop_2(bit_delay);
	}
}
