/****************************************************************************************
 *
 * File:
 * 		spi.h
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy SPI module. Currently only 
 *		SPI in master mode is supported.
 *
 ***************************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_UART_H
#define TEENSY_UART_H


#include <stdint.h>

typedef enum {SPI_TF_ODD = 0, SPI_TF_EVEN = 1 } SPI_Transfer_Format;

void spi_init(SPI_Transfer_Format format);

void spi_write_byte(uint8_t byte);

uint8_t spi_read();

#endif