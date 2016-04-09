/****************************************************************************************
 *
 * File:
 * 		gpio.c
 *
 * Purpose:
 * 		Implements functions for interacting with the GPIO pins.
 *
 *
 ***************************************************************************************/


#include "gpio.h"


#define SET_BIT(val, bit) val |= (1 << bit)
#define CLEAR_BIT(val, bit) val &= ~(1 << bit)
#define BIT_VAL(val, bit) (bit >> val) & 1


//-------------------------------------------------------------------------------------//
GPIO_MemMapPtr gpio_base_pointer(uint8_t pin)
{
	switch(pin)
	{
		case 3:
		case 4:
		case 16:
		case 17:
		case 18:
		case 19:
		case 24:
		case 33:
			return PTA_BASE_PTR;
		case 0:
		case 1:
		case 25:
		case 32:
			return PTB_BASE_PTR;
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 15:
		case 22:
		case 23:
		case 27:
		case 28:
		case 29:
		case 30:
			return PTC_BASE_PTR;
		case 2:
		case 5:
		case 6:
		case 7:
		case 8:
		case 14:
		case 20:
		case 21:
			return PTD_BASE_PTR;
		case 26:
		case 31:
			return PTE_BASE_PTR;
		default:
			return 0;
	}
}

//-------------------------------------------------------------------------------------//
PORT_MemMapPtr port_base_pointer(uint8_t pin)
{
	switch(pin)
	{
		case 3:
		case 4:
		case 16:
		case 17:
		case 18:
		case 19:
		case 24:
		case 33:
			return PORTA_BASE_PTR;
		case 0:
		case 1:
		case 25:
		case 32:
			return PORTB_BASE_PTR;
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 15:
		case 22:
		case 23:
		case 27:
		case 28:
		case 29:
		case 30:
			return PORTC_BASE_PTR;
		case 2:
		case 5:
		case 6:
		case 7:
		case 8:
		case 14:
		case 20:
		case 21:
			return PORTD_BASE_PTR;
		case 26:
		case 31:
			return PORTE_BASE_PTR;
		default:
			return 0;
	}
}

/*
* Returns the mapping of the software pin to the hardware pin.
*/
uint8_t pin_to_pin_num(uint8_t pin)
{
	switch(pin)
	{
		case 0:
			return 16;
		case 1:
			return 17;
		case 2:
			return 0;
		case 3:
			return 12;
		case 4:
			return 13;
		case 5:
			return 7;
		case 6:
			return 4;
		case 7:
			return 2;
		case 8:
		case 9:
			return 3;
		case 10:
			return 3;
		case 11:
			return 6;
		case 12:
			return 7;
		case 13:
			return 5;
		case 14:
			return 1;
		case 15:
		case 16:
			return 0;
		case 17:
			return 1;
		case 18:
			return 3;
		case 19:
			return 2;
		case 20:
			return 5;
		case 21:
			return 6;
		case 22:
			return 1;
		case 23:
			return 2;
		case 24:
			return 5;
		case 25:
			return 19;
		case 26:
			return 1;
		case 27:
			return 9;
		case 28:
			return 8;
		case 29:
			return 10;
		case 30:
			return 11;
		case 31:
			return 0;
		case 32:
			return 8;
		case 33:
			return 4;
		default:
			return 0;
	}
}


//-------------------------------------------------------------------------------------//
void gpio_set_mode(uint8_t pin, PinMode_t mode)
{
	uint8_t pinNum = pin_to_pin_num(pin);

	PORT_MemMapPtr portPtr = port_base_pointer(pin);
	GPIO_MemMapPtr basePtr = gpio_base_pointer(pin);

	/* Something has gone wrong */
	if(basePtr == 0 || portPtr == 0) { return; }

	switch(mode)
	{
		case GPIO_INPUT:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x1);  /* Enable GPIO mode */
			CLEAR_BIT(basePtr->PDDR, pinNum);		
		break;
		case GPIO_OUTPUT:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x1);  /* Enable GPIO mode */
			SET_BIT(basePtr->PDDR, pinNum);
		break;
		case ALT_FUNC_2:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x2);
		break;
		case ALT_FUNC_3:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x3);
		break;
		case ALT_FUNC_4:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x4);
		break;
		case ALT_FUNC_5:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x5);
		break;
		case ALT_FUNC_6:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x6);
		break;
		case ALT_FUNC_7:
			portPtr->PCR[pinNum] = PORT_PCR_MUX(0x7);
		break;
	}
}

//-------------------------------------------------------------------------------------//
void gpio_pin_write(uint8_t pin, LogicState_t state)
{
	uint8_t pinNum = pin_to_pin_num(pin);
	GPIO_MemMapPtr basePtr = gpio_base_pointer(pin);

	/* Something has gone wrong */
	if(basePtr == 0) { return; }

	if(state == LOGIC_HIGH)
	{
		basePtr->PSOR = 1 << pinNum;
	}
	else
	{
		basePtr->PCOR = 1 << pinNum;
	}
}

//-------------------------------------------------------------------------------------//
LogicState_t gpio_pin_read(uint8_t pin)
{
	uint8_t pinNum = pin_to_pin_num(pin);
	GPIO_MemMapPtr basePtr = gpio_base_pointer(pin);

	/* Something has gone wrong */
	if(basePtr == 0) { return LOGIC_LOW; }

	if(BIT_VAL(basePtr->PDIR, pinNum))
	{
		return LOGIC_HIGH;
	}
	else
	{
		return LOGIC_LOW;
	}
}