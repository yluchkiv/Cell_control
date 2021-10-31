#ifndef UART_H_
#define UART_H_

#include <stddef.h>
#include <stdint.h>

class uart {
      public:
	static bool init(uint32_t baud, size_t tx_size, size_t rx_size);
	static void start();
	static size_t available();
	static bool print(const char *str);
	static bool write(const uint8_t *data, size_t size);
	static size_t read(uint8_t *data, size_t size);

      private:
	static bool initialized_;
	static size_t tx_size_;
	static size_t rx_size_;
};

#endif /* UART_H_ */
