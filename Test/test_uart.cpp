#include "uart.h"

#include <gtest/gtest.h>

extern uint8_t mock_uart_ll_tx_isr();
extern uint8_t mock_uart_ll_rx_isr(uint8_t b);

TEST(UartTest, HandlesInput_Init) {
	EXPECT_EQ(uart::init(19200, 11, 11), true);
	EXPECT_EQ(uart::init(19200, 11, 11), false);
	uart::start();
	EXPECT_EQ(uart::available(), 0);

	EXPECT_EQ(uart::print("123"), true);
	EXPECT_EQ(uart::print("123456789123456789"), false);
	EXPECT_EQ(uart::available(), 0);
	EXPECT_EQ(mock_uart_ll_tx_isr(), '2');
	EXPECT_EQ(mock_uart_ll_tx_isr(), '3');

	mock_uart_ll_rx_isr('1');
	mock_uart_ll_rx_isr('0');
	mock_uart_ll_rx_isr('5');
	mock_uart_ll_rx_isr('8');
	mock_uart_ll_rx_isr('4');
	EXPECT_EQ(uart::available(), 5);
	char data[6] = {
	    '\0',
	};
	EXPECT_EQ(uart::read((uint8_t *)data, 15), 5);
	ASSERT_STREQ("10584", data);
}

TEST(UartTest, HandlesInput_InitZero) {
	EXPECT_EQ(uart::init(19200, 0, 0), false);
	EXPECT_EQ(uart::init(19200, 11, 11), false);
}
