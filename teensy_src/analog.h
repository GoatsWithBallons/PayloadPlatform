/****************************************************************************************
 *
 * File:
 * 		analog.h
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy analog pins.
 *
 *
 ***************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_IO_H
#define TEENSY_IO_H


void adc_init();

void adc_calibrate();

#endif

#ifdef __cplusplus
}
#endif

