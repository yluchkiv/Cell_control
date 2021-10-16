#include "sw_component.h"

#include <gtest/gtest.h>

TEST(ComponentTest, HandlesInputOne) {
	EXPECT_EQ(process_request(1, 1), processing_t::message);
}

TEST(ComponentTest, HandlesInputSixOne) {
	EXPECT_EQ(process_request(6, 1), processing_t::gate);
}

TEST(ComponentTest, HandlesInputSeven) {
	EXPECT_EQ(process_request(7, 7), processing_t::message);
}
