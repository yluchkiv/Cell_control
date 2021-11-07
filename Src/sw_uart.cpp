#include <string.h>
#include <util/delay.h>

#include "scope_lock.h"
#include "sw_uart.h"

uint16_t sw_uart::bit_delay_{0};
uint8_t sw_uart::reg_mask_{0};
uint8_t sw_uart::inv_mask_{0};
volatile uint8_t *sw_uart::port_{nullptr};

void sw_uart::init(uint32_t baud, volatile uint8_t *ddr, volatile uint8_t *port,
		   uint8_t pin) {
	bit_delay_ = ((F_CPU / baud) / 4) - (15 / 4);
	reg_mask_ = static_cast<uint8_t>(1 << pin);
	inv_mask_ = static_cast<uint8_t>(~(1 << pin));
	port_ = port;

	*ddr |= reg_mask_;   /* Enable GPIO output */
	*port_ |= inv_mask_; /* Set GPIO output high */
	_delay_loop_2(bit_delay_);
}

void sw_uart::print(const char *str) {
	sw_uart::write(reinterpret_cast<const uint8_t *>(str), ::strlen(str));
}

void sw_uart::write(const uint8_t *data, size_t size) {
	for (size_t i = 0; i < size; i++) {
		scope_lock sl{};

		/* start bit */
		*port_ &= inv_mask_;
		_delay_loop_2(bit_delay_);

		uint8_t b = data[i];
		/* each of the 8 bits */
		for (uint8_t bit = 8; bit > 0; bit--) {
			if (b & 1) {
				*port_ |= reg_mask_;
			} else {
				*port_ &= inv_mask_;
			}
			b >>= 1;
			_delay_loop_2(bit_delay_);
		}

		/* 2 stop bits */
		*port_ |= reg_mask_;
		_delay_loop_2(bit_delay_);
		_delay_loop_2(bit_delay_);
	}
}
