#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stddef.h>
#include <stdint.h>

class ring_buffer {
      public:
	ring_buffer(size_t buf_size);
	~ring_buffer();
	bool write(uint8_t b);
	bool read(uint8_t &b);
	size_t count();

      private:
	uint8_t *data_ = nullptr;
	size_t size_ = 0;
	size_t head_ = 0;
	size_t tail_ = 0;
};

#endif /* RING_BUFFER_H_ */
