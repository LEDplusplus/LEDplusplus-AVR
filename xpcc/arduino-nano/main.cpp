// coding: utf-8
/* Copyright (c) 2017, Raphael Lehmann
 * All Rights Reserved.
 *
 * See the file `LICENSE` for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#include <xpcc/architecture/platform.hpp>

using namespace xpcc::atmega;
using clock = xpcc::avr::SystemClock;

// Create a new UART object and configure it to a baudrate of 115200
using uart = Uart0;

int
main()
{
    GpioOutputD1::connect(Uart0::Tx);
    GpioInputD0::connect(Uart0::Rx);
    uart::initialize<clock, 115200, xpcc::Tolerance::FivePercent>();

    // Enable interrupts, this is needed for every buffered UART
	sei();

	// todo
	
	while (1)
	{
	}
}
