/****************************************************************************************
 *
 * File:
 * 		uart.h
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy UART module.
 *
 *
 ***************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_UART_H
#define TEENSY_UART_H


#include <stdint.h>
#include "common.h"


typedef enum { UART0, UART1, UART2 } UartChannel_t;


/****************************************************************************************
* Initialises and setups a uart channel and its corresponding GPIO pins.
*
* @param chnl      The UART channel to setup.
* @param baud      The baud rate of the UART channel.
*
****************************************************************************************/
void uart_init(UartChannel_t chnl, uint16_t baud);


/****************************************************************************************
 * Returns true(1) if the UART channel has characters waiting in its FIFO buffer.
 *
 * NOTE - Jordan: How big is this FIFO?
 *
 * @param chnl      The UART channel to inspect.
 *
 ****************************************************************************************/
int uart_characters_waiting(UartChannel_t chnl);


/****************************************************************************************
 * Waits until there is a available byte in the UART channel's RX FIFO buffer and then 
 * returns that character.
 *
 * @param chnl      The UART channel to read a byte from.
 *
 ****************************************************************************************/
uint8_t uart_read(UartChannel_t chnl);


/****************************************************************************************
 * Transmit a byte through the UART channel's TX line. This function will wait until 
 * there is room in the FIFO buffer before the character is added to the buffer and the 
 * function returns.
 *
 * @param chnl      The UART channel to transmit a byte across.
 * @param byte		The byte to transmit.
 *
 ****************************************************************************************/
void uart_transmit(UartChannel_t chnl, uint8_t byte);


/****************************************************************************************
 * Transmits a buffer of bytes of a given length through the UART channel's TX line. This
 * function will wait untill the whole buffer has been copied into the TX FIFIO buffer
 * before returning.
 *
 * @param chnl      The UART channel to transmit a buffer across.
 * @param buffer 	A pointer to the byte buffer to transmit
 * @param length	The number of bytes to transmit.
 *
 ****************************************************************************************/
void uart_transmit_buffer(UartChannel_t chnl, const uint8_t* buffer, uint16_t num);


/****************************************************************************************
 * Returns a UART_MemMapPtr which is a memory mapped pointer to a particular uart
 * channel.
 *
 ****************************************************************************************/
UART_MemMapPtr uart_pointer(UartChannel_t channel);


#endif

#ifdef __cplusplus
}
#endif