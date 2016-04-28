//###################################################################
//
// file: Main.cpp
//
// Contains the entry point
//
//###################################################################


#include "teensy_src/uart.h"
#include "teensy_src/gpio.h"
#include "teensy_src/pin_map.h"

int main(void)
{
    uart_init(UART0, 9600);

	/* Configure PC5 as GPIO and output */
	gpio_set_mode(13, GPIO_OUTPUT);
	gpio_write(13, LOGIC_LOW);

	uart_transmit(UART0, (uint8_t)('J'));

    if(uart_read(UART0) == (uint8_t)('J'))
    {
        gpio_write(13, LOGIC_HIGH);
    }
    else
    {
        //GPIOC_PCOR = 1 << 5;
    }
    
	return 0;
}
