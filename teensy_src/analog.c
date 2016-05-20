/****************************************************************************************
 *
 * File:
 * 		analog.c
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy pins.
 *
 *
 ***************************************************************************************/


#include "analog.h"
#include "io.h"

//-------------------------------------------------------------------------------------//
void adc_init()
{
	// Setup basic ADC module
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;

	// Calibrate the module
	adc_calibrate();

	// Configure the module
}

//-------------------------------------------------------------------------------------//
void adc_calibrate()
{
	// Start the coversion, selects the highest level of accuracy.
	ADC0_SC3 = 47;

	while(!(ADC0_SC3 & ADC_SC1_COCO_MASK));

	uint16_t calValue = ADC_CLP0_REG + ADC_CLP1_REG + ADC_CLP2_REG + ADC_CLP3_REG + ADC_CLP4_REG + ADC_CLPS_REG;
	calValue = (calValue / 2) & 8000;
	ADC0_PG = calValue;

	calValue = ADC_CLM0_REG + ADC_CLM1_REG + ADC_CLM2_REG + ADC_CLM3_REG + ADC_CLM4_REG + ADC_CLMS_REG;
	calValue = (calValue / 2) & 8000;
	ADC0_MG = calValue;
}

//-------------------------------------------------------------------------------------//
void io_analog_write(uint8_t pin, uint16_t value)
{
	
}

//-------------------------------------------------------------------------------------//
uint16_t io_analog_read(uint8_t pin)
{
	return 0;
}