#include <string.h>
#include <util/delay.h>

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

	*ddr_ |= static_cast<uint8_t>(1u << pin_);     /* Enable GPIO output */
	*port_ &= static_cast<uint8_t>(~(1u << pin_)); /* Set GPIO output low */
}

void sw_uart::print(const char *str) {
	sw_uart::write(reinterpret_cast<const uint8_t *>(str), ::strlen(str));
}

void sw_uart::write(const uint8_t *data, size_t size) {
	// TODO: implement busy wait transmit
	static_cast<void>(data);
	for (size_t i = 0; i < size; i++) {
		_delay_ms(300);
		*port_ ^= static_cast<uint8_t>(1u << pin_);
	}
}
