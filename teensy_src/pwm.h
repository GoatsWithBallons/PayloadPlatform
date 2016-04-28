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


/****************************************************************************************
* Initialises the PWM module to a set frequency, currently only the first timer is 
* implemented.
*
* @param frequency 			The frequency in hertz.
*
****************************************************************************************/
void pwm_init(uint16_t frequency);

/****************************************************************************************
* Writes a value into the PWM channel.
*
* @param pin 				The PWM pin to write to.
* @param value				The value to write.
*
****************************************************************************************/
void pwm_write(uint8_t pin, uint16_t value);

uint8_t pwm_status();


#endif