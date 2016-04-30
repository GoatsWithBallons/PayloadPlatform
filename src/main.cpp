//###################################################################
//
// file: Main.cpp
//
// Contains the entry point
//
//###################################################################


#include "teensy_src/pwm.h"
#include "teensy_src/io.h"
#include "teensy_src/pin_map.h"
#include "teensy_src/pwm.h"


int main(void)
{
    //uart_init(UART0, 9600);

	/* Configure PC5 as GPIO and output */
	io_set_pin(14, OUTPUT, GPIO);
	io_digital_write(14, LOGIC_LOW);

    io_set_pin(13, OUTPUT, GPIO);
    io_digital_write(13, LOGIC_HIGH);/*

	uart_transmit(UART0, (uint8_t)('J'));

    if(uart_read(UART0) == (uint8_t)('J'))
    {
        io_digital_write(13, LOGIC_HIGH);
    }
    else
    {
        //GPIOC_PCOR = 1 << 5;
    }*/

    pwm_init(1000);
    pwm_write(5, 750);

    while(true) {
        
    }
    
	return 0;
}
