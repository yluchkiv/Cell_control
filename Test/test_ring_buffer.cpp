#include "ring_buffer.h"

#include <gtest/gtest.h>

TEST(RingBufferTest, Test_0) { 
	EXPECT_EQ(0U, ring_buffer(0).count()); 
}

TEST(RingBufferTest, Test_1) {
	ring_buffer buf(567);

	EXPECT_EQ(0U, buf.count());

	buf.write(0);
	EXPECT_EQ(1U, buf.count());
}
TEST(RingBufferTest, Test_2){
	ring_buffer buf(234);
	buf.write(4);
	buf.write(56);
	buf.write(9);

	EXPECT_EQ(3U, buf.count());
}
TEST(RingBufferTest, Test_3){
	ring_buffer buf(4);
	buf.write(4);
	buf.write(56);
	buf.write(9);
	buf.write(7);
	buf.write(34);

	EXPECT_EQ(4U, buf.count());
}
TEST(RingBufferTest, Test_4){
	ring_buffer buf(4);
	uint8_t result;
	buf.write(4);
	buf.write(56);
	buf.write(9);
	buf.read(result);
	buf.write(7);
	buf.read(result);
	buf.write(34);
	buf.write(4);
	buf.write(56);
	buf.read(result);
	buf.write(9);
	buf.write(7);
	buf.write(34);

	EXPECT_EQ(4U, buf.count());
}
TEST(RingBufferTest, Test_5){
	ring_buffer buf(4);
	uint8_t result;
	buf.read(result);
	EXPECT_EQ(0U, buf.count());
}
TEST(RingBufferTest, Test_6){
	ring_buffer buf(4);
	uint8_t result;
	buf.write(34);
	buf.write(4);
	buf.write(56);
	buf.read(result);
	EXPECT_EQ(2U, buf.count());
	EXPECT_EQ(34, result);
	buf.read(result);
	EXPECT_EQ(1U, buf.count());
	EXPECT_EQ(4, result);
	buf.read(result);
	EXPECT_EQ(0U, buf.count());
	EXPECT_EQ(56, result);
	buf.write(34);
	buf.write(4);
	buf.write(56);
	buf.read(result);
	EXPECT_EQ(2U, buf.count());
	EXPECT_EQ(34, result);
	buf.read(result);
	EXPECT_EQ(1U, buf.count());
	EXPECT_EQ(4, result);
	buf.read(result);
	EXPECT_EQ(0U, buf.count());
	EXPECT_EQ(56, result);
}