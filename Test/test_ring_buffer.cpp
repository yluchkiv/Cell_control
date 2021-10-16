#include "ring_buffer.h"

#include <gtest/gtest.h>

TEST(RingBufferTest, Test_0) { EXPECT_EQ(0, ring_buffer(0).count()); }

TEST(RingBufferTest, Test_1) {
	ring_buffer buf(567);

	EXPECT_EQ(0, buf.count());

	buf.write(0);
	EXPECT_EQ(1, buf.count());
}
