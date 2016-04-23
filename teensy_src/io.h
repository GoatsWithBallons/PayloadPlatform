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


 #ifndef TEENSY_IO_H
 #define TEENSY_IO_H


/* Defines the states a gpio pin can be in */
typedef enum { LOGIC_LOW = 0, LOGIC_HIGH = 1 } LogicLevel;

/* Defines the operating modes a pin can be in */
typedef enum { ALT_FUNC_0, GPIO, ALT_FUNC_2, ALT_FUNC_3, ALT_FUNC_4, ALT_FUNC_5, ALT_FUNC_6, ALT_FUNC_7 } PinFunc;

/* Defines the pin direction */
typedef enum { GPIO_INPUT, GPIO_OUTPUT } PinDir;


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

void io_analog_write(uint8_t pin, uint16_t value);

uint16_t io_analog_read(uint8_t pin);

 #endif