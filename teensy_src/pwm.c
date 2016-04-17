/****************************************************************************************
 *
 * File:
 * 		pwm.c
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy FTM module.
 *
 *
 ***************************************************************************************/


#include "pwm.h"
#include "gpio.h"
#include "status_defs.h"
#include "pin_map.h"

/* Register defines */

/* FTM Status and Control Register */
#define SC_CLKS_SYS_CLK		0x8			/* Clock Source - System Clk */
#define SC_PS_8				0x3
#define SC_PS_16			0x4
#define SC_PS_32			0x5


int8_t status = STATUS_NOT_INITIALISED;

//-------------------------------------------------------------------------------------//
void pwm_init(uint16_t frequency)
{
	/* Enable the module clock */
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;

	FTM0_OUTMASK = 0xFF;					/* Disable outputs while we set stuff up */
	FTM0_SC = SC_CLKS_SYS_CLK;				/* Set the clock source to the sys clk */
	FTM0_MOD = (CPU_FREQUENCY / frequency);	/* Set the modulus */
	FTM0_CNTIN = 0;							/* Set the timer counter to 0 */
	FTM0_CNT = 0;
	FTM0_MODE = 1;							/* Enables the FTM */
	FTM0_OUTMASK = 0x00;

	status = STATUS_OK;
}

//-------------------------------------------------------------------------------------//
void pwm_write(uint8_t pin, uint16_t value)
{
	if(status == STATUS_NOT_INITIALISED)
	{
		return;
	}

	switch(pin)
	{
		case PWM0:
			status = STATUS_PIN_NOT_SUPPORTED;
			return;
		break;
		case PWM1:
			status = STATUS_PIN_NOT_SUPPORTED;
			return;
		break;
		case PWM2:
			gpio_set_mode(pin, ALT_FUNC_4);
			FTM0_CnV(7) = value;
		break;
		case PWM3:
			gpio_set_mode(pin, ALT_FUNC_4);
			FTM0_CnV(4) = value;
		break;
		case PWM4:
			gpio_set_mode(pin, ALT_FUNC_4);
			FTM0_CnV(0) = value;
		break;
		case PWM5:
			gpio_set_mode(pin, ALT_FUNC_4);
			FTM0_CnV(1) = value;
		break;
		default:
			status = STATUS_WRONG_PIN;
			return;
	}

  	FTM0_SYNC |= 0x80;
}

uint8_t pwm_module_status()
{
	uint8_t status = STATUS_NOT_INITIALISED;

	if(spi_status != STATUS_NOT_INITIALISED)
	{
		status = spi_status;
		spi_status = STATUS_OK;
	}
	
	return status;
}