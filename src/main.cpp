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
#include "inc/ring_buffer.h"

int main(void)
{
    ring_buffer buffer;
    ring_buffer_init(buffer);
    //uart_init(UART0, 9600);

    /* Configure PC5 as GPIO and output */
    io_set_pin(14, OUTPUT, GPIO);
    io_digital_write(14, LOGIC_LOW);

    io_set_pin(13, OUTPUT, GPIO);
    io_digital_write(13, LOGIC_HIGH);

    pwm_init(1000);

	 while(true) {
        pwm_write(5, 500);
        io_digital_write(14, LOGIC_HIGH);
        for (int i=0; i<1000000; ){i++; }
        pwm_write(5, 500);
        io_digital_write(14, LOGIC_LOW);
        for (int i=0; i<1000000; ){i++; }
    }
    
	return 0;
}
