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

TEST(RingBufferTest, ZeroSize) {
	ring_buffer buf(0);
	EXPECT_EQ(buf.count(), 0);

	EXPECT_EQ(buf.write(255), false);
	EXPECT_EQ(buf.count(), 0);
}

TEST(RingBufferTest, BufferCount) {
	ring_buffer buf(567);

	EXPECT_EQ(buf.count(), 0);

	buf.write(0);
	buf.write(5);
	EXPECT_EQ(buf.count(), 2);
}

TEST(RingBufferTest, BufferOverflow) {
	ring_buffer buf(2);
	EXPECT_EQ(buf.write(3), true);
	EXPECT_EQ(buf.write(4), false);

	uint8_t d;
	EXPECT_EQ(buf.read(d), true);
	EXPECT_EQ(d, 3);
}

TEST(RingBufferTest, RollOver) {
	ring_buffer buf(2);
	EXPECT_EQ(buf.write(3), true);
	EXPECT_EQ(buf.write(4), false);

	uint8_t d;
	EXPECT_EQ(buf.read(d), true);
	EXPECT_EQ(d, 3);

	EXPECT_EQ(buf.write(5), true);
	EXPECT_EQ(buf.read(d), true);
	EXPECT_EQ(d, 5);
}

TEST(RingBufferTest, BufferUnderflow) {
	ring_buffer buf(2);
	uint8_t d;
	EXPECT_EQ(buf.read(d), false);
}
