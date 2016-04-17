/****************************************************************************************
 *
 * File:
 * 		spi.c
 *
 * Purpose:
 * 		Provides functions for interacting with the teensy SPI module. Currently only 
 *		SPI in master mode is supported.
 *
 ***************************************************************************************/


#include "spi.h"
#include "common.h"
#include "gpio.h"
#include "pin_map.h"
#include "status_defs.h"

int8_t spi_status = STATUS_NOT_INITIALISED;

//-------------------------------------------------------------------------------------//
void spi_init(SPI_Transfer_Format format)
{
	/* Enable the module clock */
	SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;

	/* Ensure we are halted before configuring, the TXRXS bit indicates the state of
	   the module */
	SPI0_MCR |= SPI_MCR_HALT_MASK;
	while( (SPI_SR_TXRXS_MASK & SPI0_SR) );

	gpio_set_mode(SPI_SCK, ALT_FUNC_2);
	gpio_set_mode(SPI_DOUT, ALT_FUNC_2);
	gpio_set_mode(SPI_DIN, ALT_FUNC_2);

	/* Set the SPI mode to master, Set chip select inactive to be logic high */
	SPI0_MCR |= SPI_MCR_MSTR_MASK | SPI_MCR_PCSIS(0x1F);

	/* Set the clock phase and frame size for the two buffers */
	uint32_t ctar0 = (format == 0 ? 0 : SPI_CTAR_CPHA_MASK) | SPI_CTAR_FMSZ(7);
	uint32_t ctar1 = (format == 0 ? 0 : SPI_CTAR_CPHA_MASK) | SPI_CTAR_FMSZ(15);

	/* Update registers */
	SPI0_CTAR0 = ctar0;
	SPI0_CTAR1 = ctar1;

	/* Clear the RX and TX FIFOs */
	SPI0_MCR |= SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;

	/* Unhalt the module */
	SPI0_MCR &= ~SPI_MCR_HALT_MASK;

	spi_status = STATUS_OK;
}

//-------------------------------------------------------------------------------------//
void spi_write_byte(uint8_t byte)
{
	if(spi_status != STATUS_NOT_INITIALISED)
	{
		/* Flush TX FIFO */
		SPI0_MCR |= SPI_MCR_CLR_TXF_MASK;

		/* Clears the transfer flag */
		SPI0_SR |= SPI_SR_TCF_MASK;

		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | SPI_PUSHR_CTAS(0) | byte;

		/* Wait for the transfer */
		while( !(SPI0_SR & SPI_SR_TCF_MASK) );
	}
}

//-------------------------------------------------------------------------------------//
uint8_t spi_read()
{
	if(spi_status != STATUS_NOT_INITIALISED)
	{
		/* Flush RX FIFO */
		SPI0_MCR |= SPI_MCR_CLR_RXF_MASK;

		/* Clears the transfer flag */
		SPI0_SR |= SPI_SR_TCF_MASK;

		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | 0xFF;

		/* Wait for the transfer */
		while( !(SPI0_SR & SPI_SR_TCF_MASK) );

		return SPI0_POPR;
	}
}

//-------------------------------------------------------------------------------------//
void spi_write_bytes(uint8_t* buffer, uint16_t length)
{
	if(spi_status == STATUS_NOT_INITIALISED)
	{
		return;
	}

	if(length == 0 || buffer == 0)
	{
		spi_status = STATUS_EMPTY_NULL_DATA;
		return;
	}

	/* Flush TX FIFO */
	SPI0_MCR |= SPI_MCR_CLR_TXF_MASK;

	uint8_t oddNumber = 0;

	if(length % 2 != 0)
	{
		oddNumber = 1;
	}

	uint16_t temp;

	for(int i = 0; i < length - 2; i+=2)
	{
		/* Wait for room in the TX FIFO */
		while( !(SPI0_SR & SPI_SR_TFFF_MASK) );

		temp = (buffer[i] << 8) | buffer[i + 1];
		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | SPI_PUSHR_CTAS(1) | temp;

		/* Clear the end of queue flag, we want to ensure this is reset incase we
		   we are interrupted. */
		SPI0_SR |= SPI_SR_EOQF_MASK;
	}

	/* Transfer the last byte */ 
	if(oddNumber == 1)
	{
		while( !(SPI0_SR & SPI_SR_TFFF_MASK) );
		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | SPI_PUSHR_CTAS(0) | buffer[length - 1];
	}

	/* Wait for transfer to complete */
	while( !(SPI0_SR & SPI_SR_EOQF_MASK));
}

//-------------------------------------------------------------------------------------//
void spi_read_bytes(uint8_t* buffer, uint16_t length)
{
	if(spi_status == STATUS_NOT_INITIALISED)
	{
		return;
	}

	if(length == 0 || buffer == 0)
	{
		spi_status = STATUS_EMPTY_NULL_DATA;
		return;
	}

	/* Flush RX FIFO */
	SPI0_MCR |= SPI_MCR_CLR_RXF_MASK;
	SPI0_PUSHR = SPI_PUSHR_CONT_MASK | SPI_PUSHR_CTAS(1) | 0xFFFF;

	uint8_t oddNumber = 0;

	if(length % 2 != 0)
	{
		oddNumber = 1;
	}

	uint16_t temp;

	/* Clears the transfer flag */
	SPI0_SR |= SPI_SR_TCF_MASK;

	for(int i = 0; i < length - 2; i+=2)
	{
		/* Wait for the transfer */
		while( !(SPI0_SR & SPI_SR_TCF_MASK) );
		SPI0_SR |= SPI_SR_TCF_MASK;

		/* Pop off the value from the RX FIFO */
		temp = SPI0_POPR;

		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | SPI_PUSHR_CTAS(1) | 0xFFFF;

		buffer[i] = SPI0_POPR >> 8;
		buffer[i + 1] = SPI0_POPR;
	}

	/* Transfer the last byte */ 
	if(oddNumber == 1)
	{
		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | SPI_PUSHR_CTAS(0) | 0xFFFF;

		/* Wait for the transfer */
		while( !(SPI0_SR & SPI_SR_TCF_MASK) );

		buffer[length - 1] = SPI0_POPR;
	}
}

//-------------------------------------------------------------------------------------//
uint8_t spi_status()
{
	uint8_t status = STATUS_NOT_INITIALISED;

	if(spi_status != STATUS_NOT_INITIALISED)
	{
		status = spi_status;
		spi_status = STATUS_OK;
	}
	
	return status;
}
