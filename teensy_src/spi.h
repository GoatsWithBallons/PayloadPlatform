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
* return when the buffer has been transmitted. If the buffer is null or length is 0 then 
* the module status code will be STATUS_EMPTY_NULL_DATA.
*
* @param buffer 			The buffer to transmit.
* @param length				The number of items in the buffer to transmit.
*
****************************************************************************************/
void spi_write_bytes(uint8_t* buffer, uint16_t length);

/****************************************************************************************
* Reads a byte buffer frome the SPI RX FIFO. If the buffer is null or length is 0 then 
* the module status code will be STATUS_EMPTY_NULL_DATA.
*
* @param buffer 			The buffer to receive data into.
* @param length				The number of items to receive.
*
****************************************************************************************/
void spi_read_bytes(uint8_t* buffer, uint16_t length);

/****************************************************************************************
* Returns SPI module status, possible codes are:
* 	1	STATUS_OK				: Indicates everything is setup and working
*	0	STATUS_NOT_INITIALISED	: Indicates the module wasn't initialised, call spi_init
*	-1	STATUS_EMPTY_NULL_DATA	: A null data pointer or data buffer of size 0 was 
*								  given to the module.
*
* If the status is anything apart from STATUS_NOT_INITIALISED it is reset to STATUS_OK on
* this functions calling.
*
* @returns					A status code.		
*
****************************************************************************************/
uint8_t spi_status();

#endif

#ifdef __cplusplus
}
#endif