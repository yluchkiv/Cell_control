#include <avr/interrupt.h>

#include "scope_lock.h"

scope_lock::scope_lock() {
	enabled_interrupts_ = SREG;
	cli();
}
scope_lock::~scope_lock() {
	SREG = enabled_interrupts_;
	asm volatile("" ::: "memory");
}
