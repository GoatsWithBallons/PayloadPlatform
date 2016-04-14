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


int spi_setup = 0;

//-------------------------------------------------------------------------------------//
void spi_init(SPI_Transfer_Format format)
{
	/* Enable the module clock */
	SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;

	/* Ensure we are halted before configuring, the TXRXS bit indicates the state of
	   the module */
	SPI0_MCR |= SPI_MCR_HALT_MASK;
	while( (SPI_SR_TXRXS_MASK & SPI0_SR) );

	// TODO - Jordan: Setup pins

	/* Set the SPI mode to master, Set chip select inactive to be logic high */
	SPI0_MCR |= SPI_MCR_MSTR_MASK | SPI_MCR_PCSIS(0x1F);

	/* Set the clock phase and the frame size to 8 (7 + 1)*/
	uint32_t ctar0 = (format == 0 ? 0 : SPI_CTAR_CPHA_MASK) | SPI_CTAR_FMSZ(7);

	/* Update registers */
	SPI0_CTAR0 = ctar0;

	/* Clear the RX and TX FIFOs */
	SPI0_MCR |= SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;

	/* Unhalt the module */
	SPI0_MCR &= ~SPI_MCR_HALT_MASK;

	spi_setup = 1;
}

//-------------------------------------------------------------------------------------//
void spi_write_byte(uint8_t byte)
{
	if(spi_setup == 1)
	{
		/* Flush RX & TX FIFOs */
		SPI0_MCR |= SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;

		/* Clears the transfer flag */
		SPI0_SR |= SPI_SR_TCF_MASK;

		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | byte;

		/* Wait for the transfer */
		while( !(SPI0_SR & SPI_SR_TCF_MASK) );
	}
	else
	{
		// TODO - Jordan: Set some kind of error reporting
	}
}

//-------------------------------------------------------------------------------------//
uint8_t spi_read()
{
	if(spi_setup == 1)
	{
		/* Flush RX & TX FIFOs */
		SPI0_MCR |= SPI_MCR_CLR_RXF_MASK | SPI_MCR_CLR_TXF_MASK;

		/* Clears the transfer flag */
		SPI0_SR |= SPI_SR_TCF_MASK;

		SPI0_PUSHR = SPI_PUSHR_CONT_MASK | 0xFF;

		/* Wait for the transfer */
		while( !(SPI0_SR & SPI_SR_TCF_MASK) );

		return SPI0_POPR;
	}
	else
	{
		// TODO - Jordan: Set some kind of error reporting
	}
}
