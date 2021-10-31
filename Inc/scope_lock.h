#ifndef SCOPE_LOCK_H_
#define SCOPE_LOCK_H_

#include <stddef.h>
#include <stdint.h>

class scope_lock {
	scope_lock(const scope_lock &) = delete;
	scope_lock(scope_lock &&) = delete;
	scope_lock &operator=(const scope_lock &) = delete;
	scope_lock &operator=(scope_lock &&) = delete;
	uint8_t enabled_interrupts_{0u};

      public:
	scope_lock();
	~scope_lock();
};

#endif /* SCOPE_LOCK_H_ */
