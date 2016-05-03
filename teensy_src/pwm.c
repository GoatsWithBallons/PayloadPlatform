/****************************************************************************************
 *
 * File:
 * 		pwm.c
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy FTM module.
 *
 * Developer Notes:
 *		The PWM module is setup in edge-aligned mode. The internal counter (FTM_CNT) 
 *		counts up to the parameter mod provided in pwm_init. When the counter reaches 
 *		this value the module will send a pulse.
 *
 *		The PWM period is determined by (MOD - CNTIN + 1). The counter updaters every 
 *		8th system clock tick, so 9MHz I believe.
 *
 *
 ***************************************************************************************/


#include "pwm.h"
#include "io.h"
#include "status_defs.h"
#include "pin_map.h"

/* Register defines */

/* FTM Status and Control Register */
#define REG_SC_CLKS_SYS_CLK		0x8				/* Clock Source - System Clk */
#define REG_SC_PS_4				FTM_SC_PS(3)	/* Clock divider 8

/* FTM Mode register */
#define REG_MODE_WPDIS			(1 << 2)		/* Write protection disabled */
#define REG_MODE_ENABLE			(1 << 0)		/* Enables all FTM registers */

/* FTM Channel (n) Status and Control */
#define REG_CNSC_ELSB			(1 << 3)		/* Edge or Level select, see channel mode */
#define REG_CNSC_MSB			(1 << 5)		/* Channel mode select, see channel mode */


static int8_t status = STATUS_NOT_INITIALISED;

//-------------------------------------------------------------------------------------//
void pwm_init(uint16_t mod)
{
	// Module Clock
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;

	// Have to clear the status and control register before writing to it
	FTM0_SC = 0;

	// Remove write protection and enable all registers.
	//FTM0_MODE = REG_MODE_WPDIS | REG_MODE_ENABLE;

	FTM0_MOD = mod;

	// Setup the channels
	FTM0_C0SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C1SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C2SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C3SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C4SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C5SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C6SC = REG_CNSC_MSB | REG_CNSC_ELSB;
	FTM0_C7SC = REG_CNSC_MSB | REG_CNSC_ELSB;

	FTM0_CNTIN = 0;			/* Set the timer counter to 0 */
	FTM0_QDCTRL = 0;
	FTM0_COMBINE = 0;

	// Set the PWM clock source, enabling the module
	FTM0_SC = REG_SC_CLKS_SYS_CLK | REG_SC_PS_4;	

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
		case PWM1:
			status = STATUS_PIN_NOT_SUPPORTED;
			return;
		break;
		case PWM2:
			io_set_pin(pin, OUTPUT, ALT_FUNC_4);
			FTM0_C7V = value;
		break;
		case PWM3:
			io_set_pin(pin, OUTPUT, ALT_FUNC_4);
			FTM0_C4V = value;
		break;
		case PWM4:
			io_set_pin(pin, OUTPUT, ALT_FUNC_4);
			FTM0_C0V = value;
		break;
		case PWM5:
			io_set_pin(pin, OUTPUT, ALT_FUNC_4);
			FTM0_C1V = value;
		break;
		default:
			status = STATUS_WRONG_PIN;
			return;
	}

  	FTM0_SYNC |= 0x80;
}

uint8_t pwm_status()
{
	uint8_t result = STATUS_NOT_INITIALISED;

	if(status != STATUS_NOT_INITIALISED)
	{
		result = status;
		status = STATUS_OK;
	}
	
	return result;
}