/****************************************************************************************
 *
 * File:
 * 		pwm.h
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy FTM module.
 *
 *
 ***************************************************************************************/

 #ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_UART_H
#define TEENSY_UART_H


#include <stdint.h>
#include "common.h"


#define CPU_FREQUENCY 72000000 /* 72MHz */


typedef enum { 
	CHNL0 = 0, CHNL1 = 1, CHNL2 = 2, CHNL3 = 3, 
	CHNL4  = 4, CHNL5 = 5, CHNL6 = 6, CHNL7 = 7, 
} Pwm_Channel_t;

/****************************************************************************************
* Initialises the PWM module to a set frequency, currently only the first timer is 
* implemented.
*
* @param frequency 			The frequency in hertz.
*
****************************************************************************************/
void pwm_init(uint16_t frequency);

/****************************************************************************************
* Writes a value into the PWM channel. The GPIO pin still needs to be setup
*
* @param chnl 				The channel.
* @param value				The value to write.
*
****************************************************************************************/
void pwm_write(Pwm_Channel_t chnl, uint16_t value);


#endif