//###################################################################
//
// file: Main.cpp
//
// Contains the entry point
//
//###################################################################


#include  "teensy_src/teensy3x.h"
#include "teensy_src/uart.h"

int main(void)
{
	//volatile uint32_t n;
    //uart_init(UART0, 9600);

	/* Configure PC5 as GPIO (alt = 0x01), and output */
	//PORTC_PCR5 = PORT_PCR_MUX(0x1);
	//GPIOC_PDDR = 1 << 5;
	//GPIOC_PCOR = 1 << 5; /* LED off */

    //uart.Transmit('J');

    /*if(uart.Receive() == 'J')
    {
        GPIOC_PSOR = 1 << 5;
    }
    else
    {
        GPIOC_PCOR = 1 <<5;
    }*/

	while (1) {
		//GPIOC_PSOR = 1 << 5; /* LED on */
		//for (n = mcg_clk_hz / 100; n; n--); /* delay */
		//GPIOC_PCOR = 1 << 5; /* LED off */
		//for (n = mcg_clk_hz / 200; n; n--); /* delay */
	}
	return 0;
}
