#ifndef SW_UART_H_
#define SW_UART_H_

#include <stddef.h>
#include <stdint.h>

class sw_uart {
      public:
	static void init(uint32_t baud, volatile uint8_t *ddr,
			 volatile uint8_t *port, uint8_t pin);
	static void print(const char *str);
	static void write(const uint8_t *data, size_t size);

      private:
	static uint16_t bit_delay_;
	static uint8_t reg_mask_;
	static uint8_t inv_mask_;
	static volatile uint8_t *port_;
};

#endif /* SW_UART_H_ */
