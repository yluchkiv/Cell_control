#include "sw_component.h"

#include <gtest/gtest.h>

TEST(ComponentTest, HandlesInputOnes) {
	EXPECT_EQ(process_request(1, 1), processing_t::message);
}
