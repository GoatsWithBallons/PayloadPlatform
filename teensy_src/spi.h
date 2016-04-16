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

/****************************************************************************************
* Initialises the SPI module.
*
* @param format 			The frame format. 		
*
****************************************************************************************/
void spi_init(SPI_Transfer_Format format);

/****************************************************************************************
* Writes a single byte to the SPI TX FIFO which is then transmitted. This function will
* return when the byte has been transmitted.
*
* @param byte 				The byte to transmit.		
*
****************************************************************************************/
void spi_write_byte(uint8_t byte);

/****************************************************************************************
* Reads a single byte from the SPI RX FIFO.
*
* @returns					A byte.		
*
****************************************************************************************/
uint8_t spi_read();

/****************************************************************************************
* Writes a byte buffer to the SPI TX FIFO which is then transmitted. This function will
* return when the buffer has been transmitted. The buffer must be big enough.
*
* @param buffer 			The buffer to transmit.
* @param length				The number of items in the buffer to transmit.
*
****************************************************************************************/
void spi_write_bytes(uint8_t* buffer, uint16_t length);

/****************************************************************************************
* Reads a byte buffer frome the SPI RX FIFO. The buffer must be big enough
*
* @param buffer 			The buffer to receive data into.
* @param length				The number of items to receive.
*
****************************************************************************************/
void spi_read_bytes(uint8_t* buffer, uint16_t length);

#endif