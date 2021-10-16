#include "sw_component.h"

static processing_t send_msg() { return processing_t::message; }

static processing_t open_gate() { return processing_t::gate; }

processing_t process_request(int a, int b) {
	processing_t result = processing_t::message;

	if (a > 5 && b < 3) {
		result = open_gate();
	} else {
		result = send_msg();
	}

	return result;
}
