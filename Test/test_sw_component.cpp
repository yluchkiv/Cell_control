#include "sw_component.h"

#include <gtest/gtest.h>

TEST(ComponentTest, HandlesInputOne) {
	EXPECT_EQ(process_request(1, 1), processing_t::message);
}
