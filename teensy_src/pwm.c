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

/* Register defines */

/* FTM Status and Control Register */
#define SC_CLKS_SYS_CLK		0x8			/* Clock Source - System Clk */
#define SC_PS_8				0x3
#define SC_PS_16			0x4
#define SC_PS_32			0x5


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
}

//-------------------------------------------------------------------------------------//
void pwm_write(Pwm_Channel_t chnl, uint16_t value)
{
	FTM0_CnV(chnl) = value; 
  	FTM0_SYNC |= 0x80;
}