/****************************************************************************************
 *
 * File:
 * 		gpio.h
 *
 * Purpose:
 * 		Provides functions for interacting with the GPIO pins.
 *
 *
 ***************************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_GPIO_H
#define TEENSY_GPIO_H

#include "MK20D7.h"

/* Defines the states a gpio pin can be in */
typedef enum { LOGIC_LOW = 0, LOGIC_HIGH = 1 } LogicState_t;

/* Defines the operating modes a pin can be in */
typedef enum { GPIO_INPUT, GPIO_OUTPUT, ALT_FUNC_2, ALT_FUNC_3, ALT_FUNC_4, ALT_FUNC_5, ALT_FUNC_6, ALT_FUNC_7 } PinMode_t;


/****************************************************************************************
* Sets the operating mode of the GPIO pin.
*
* @param pin 		The GPIO pin whose mode is being set.
* @param state 		The new mode.
*
****************************************************************************************/
void gpio_set_mode(uint8_t pin, PinMode_t mode);


/****************************************************************************************
* Writes a new logic state to a specific GPIO pin.
*
* @param pin 		The GPIO pin whose state is being set.
* @param state 		The new logic state.
*
****************************************************************************************/
void gpio_write(uint8_t pin, LogicState_t state);


/****************************************************************************************
* Reads the logic state of a specific GPIO pin.
*
* @param pin 		The GPIO pin whose state is being read.
*
* @returns	 		The logic state of the GPIO pin.
*
****************************************************************************************/
LogicState_t gpio_read(uint8_t pin);


#endif

#ifdef __cplusplus
}
#endif