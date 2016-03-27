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
GPIO_MemMapPtr gpio_base_pointer(GPIO_Port_t port)
{
	switch(port)
	{
		case PORT_A:
			return PTA_BASE_PTR;
		break;
		case PORT_B:
			return PTB_BASE_PTR;
		break;
		case PORT_C:
			return PTC_BASE_PTR;
		break;
		case PORT_D:
			return PTD_BASE_PTR;
		break;
		case PORT_E:
			return PTE_BASE_PTR;
		break;
		default:
			return 0;
	}
}

//-------------------------------------------------------------------------------------//
PORT_MemMapPtr port_base_pointer(GPIO_Port_t port)
{
	switch(port)
	{
		case PORT_A:
			return PORTA_BASE_PTR;
		break;
		case PORT_B:
			return PORTB_BASE_PTR;
		break;
		case PORT_C:
			return PORTC_BASE_PTR;
		break;
		case PORT_D:
			return PORTD_BASE_PTR;
		break;
		case PORT_E:
			return PORTE_BASE_PTR;
		break;
		default:
			return 0;
	}
}


//-------------------------------------------------------------------------------------//
void gpio_set_mode(GPIO_Port_t port, uint8_t pinNum, PinMode_t mode)
{
	PORT_MemMapPtr portPtr = port_base_pointer(port);
	GPIO_MemMapPtr basePtr = gpio_base_pointer(port);

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
void gpio_pin_write(GPIO_Port_t port, uint8_t pinNum, LogicState_t state)
{
	GPIO_MemMapPtr basePtr = gpio_base_pointer(port);

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
LogicState_t gpio_pin_read(GPIO_Port_t port, uint8_t pinNum)
{
	GPIO_MemMapPtr basePtr = gpio_base_pointer(port);

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