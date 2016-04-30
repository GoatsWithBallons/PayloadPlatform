/****************************************************************************************
 *
 * File:
 * 		io.h
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy pins.
 *
 *
 ***************************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_IO_H
#define TEENSY_IO_H


#include "stdint.h"


/* Defines the states a gpio pin can be in */
typedef enum { LOGIC_LOW = (uint8_t)0, LOGIC_HIGH = 1 } LogicLevel;

/* Defines the operating modes a pin can be in */
typedef enum { ALT_FUNC_0 = (uint16_t)0x0, GPIO = 0x1, ALT_FUNC_2 = 0x2, ALT_FUNC_3 = 0x3, ALT_FUNC_4 = 0x4, 
				ALT_FUNC_5 = 0x6, ALT_FUNC_6 = 0x7, ALT_FUNC_7 = 0x8 } PinFunc;

/* Defines the pin direction */
typedef enum { INPUT, OUTPUT } PinDir;


/****************************************************************************************
* Setups a IO pin for operation.
*
* @param pin 		The pin being setup
* @param dir 		The pin's desired direction, OUTPUT(1) or INPUT(0)
* @param func 		The pin's function, ALT_FUNC_0, GPIO, ALT_FUNC_2, ALT_FUNC_3, 
*					ALT_FUNC_4, ALT_FUNC_5, ALT_FUNC_6, ALT_FUNC_7
*
****************************************************************************************/
void io_set_pin(uint8_t pin, PinDir dir, PinFunc func);

/****************************************************************************************
* Writes a new logic state to a specific digital IO pin.
*
* @param pin 		The digital pin whose state is being set.
* @param logicLevel	The new logic state.
*
****************************************************************************************/
void io_digital_write(uint8_t pin, LogicLevel logicLevel);

/****************************************************************************************
* Reads the logic state of a specific digital IO pin.
*
* @param pin 		The digital pin whose state is being read.
*
* @returns	 		The logic state of the GPIO pin.
*
****************************************************************************************/
LogicLevel io_digital_read(uint8_t pin);

/****************************************************************************************
* Writes an analog value to the provided IO pin.
*
* @param pin 		The analog pin to write to.
*
****************************************************************************************/
void io_analog_write(uint8_t pin, uint16_t value);

/****************************************************************************************
* Reads an analog value from a analog pin.
*
* @param pin 		The analog pin to read.
*
* @returns	 		The logic state of the GPIO pin.
*
****************************************************************************************/
uint16_t io_analog_read(uint8_t pin);

#endif

#ifdef __cplusplus
}
#endif