/****************************************************************************************
 *
 * File:
 *    	uart.c
 *
 * Purpose:
 *    Implements the UART functions defined in uart.h
 *
 ***************************************************************************************/


#include "uart.h"


//-------------------------------------------------------------------------------------//
 void uart_init(UartChannel_t chnl, uint16_t baud)
 {
 	register uint16_t sbr, brfa;
    uint8_t temp;
    UART_MemMapPtr uart_base;
    uint32_t sys_clk;

    /* Gets the pointer to the base of the uart */
    uart_base = uart_pointer(chnl);

    /* Set the sysclk, UART0 and UART1 use the core clock, while UART2 uses the 
     * peripheral clock */
    if(chnl == UART2)
    {
        /* core_clk_khz is defined in common.h */
        sys_clk = periph_clk_khz; 
    }
    else
    {
        /* perip_clk_khz is defined in common.h */
        sys_clk = core_clk_khz;    
    }

    /* Enable the clock to the selected channel */
    switch(chnl)
    {
        case UART0:
            SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
            break;
        case UART1:            
            SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;
            break;
        case UART2:
            SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
            break;
    }

    /* Disables the transmitter and receiver while we make changes */
    UART_C2_REG(uart_base) &= ~(UART_C2_TE_MASK | /* Disable transmitter */
                                UART_C2_RE_MASK | /* Disable receiver */
                                UART_C2_RIE_MASK);/* Disable receive interrupt on buffer full */

    /* Configure the UART for 8-bit mode and no parity */
    UART_C1_REG(uart_base) = 0;

    /* Calculate baud rate */
    sbr = (uint16_t)( (sys_clk * 1000) / (baud * 16)  );

    /* Save the current value of UARTx_BDH */
    temp = UART_BDH_REG(uart_base) & ~( UART_BDH_SBR(0x1F) );

    UART_BDH_REG(uart_base) = temp | UART_BDH_SBR( (sbr & 0x1F00) >> 8);
    UART_BDL_REG(uart_base) = (uint8_t)(sbr & UART_BDL_SBR_MASK);

    /* Determine if a fractional divider is needed to get closer to the baud rate */
    brfa = ( ( (sys_clk * 32000) / (baud * 16) ) - (sbr * 32) );
    
    /* Save the current value of the UARTx_C4 register except the BRFA field */
    temp = UART_C4_REG(uart_base) &~ (UART_C4_BRFA(0x1F) );

    UART_C4_REG(uart_base) = temp | UART_C4_BRFA(brfa);

    /* Enable receiver, transmitter */
    UART_C2_REG(uart_base) |= ( UART_C2_TE_MASK | /* Enable transmitter */
                                UART_C2_RE_MASK); /* Enable receiver */

    /* Setup GPIO pins by selecting the alternative function */
    switch(chnl)
    {
        case UART0:
            PORTB_PCR17 = PORT_PCR_MUX(0X3); /* UART0 TXD */
            PORTB_PCR16 = PORT_PCR_MUX(0X3); /* UART0 RXD */
            break;
        case UART1:
            PORTC_PCR4 = PORT_PCR_MUX(0X3); /* UART1 TXD */
            PORTC_PCR3 = PORT_PCR_MUX(0X3); /* UART1 RXD */
            break;
        case UART2:
            PORTD_PCR3 = PORT_PCR_MUX(0X3); /* UART2 TXD */
            PORTD_PCR2 = PORT_PCR_MUX(0X3); /* UART2 RXD */
    }
 }

//-------------------------------------------------------------------------------------//
int uart_characters_waiting(UartChannel_t chnl)
{
	return (UART_S1_REG( uart_pointer(chnl) ) & UART_S1_RDRF_MASK);
}

//-------------------------------------------------------------------------------------//
uint8_t uart_read(UartChannel_t chnl)
{
	UART_MemMapPtr uart_base = uart_pointer(chnl);

    /* Wait untill a character has been received */
    while( !(UART_S1_REG(uart_base) & UART_S1_RDRF_MASK) );

    /* Return a received byte */
    return UART_D_REG(uart_base);
}

//-------------------------------------------------------------------------------------//
void uart_transmit(UartChannel_t chnl, uint8_t byte)
{
	UART_MemMapPtr uart_base = uart_pointer(chnl);

    /* Wait until space is available in the FIFO */
    while( !( UART_S1_REG(uart_base) & UART_S1_TDRE_MASK ) );
    
    /* Transmit the character */
    UART_D_REG(uart_base) = byte;
}

//-------------------------------------------------------------------------------------//
void uart_transmit_buffer(UartChannel_t chnl, const uint8_t* buffer, uint16_t num)
{
	for(uint16_t len = 0; len < num; len++)
	{
		uart_transmit(chnl, buffer[len]);
	}
}

//-------------------------------------------------------------------------------------//
UART_MemMapPtr uart_pointer(UartChannel_t channel)
{
    UART_MemMapPtr ptr;

    switch(channel)
    {
        case UART0:
            ptr = UART0_BASE_PTR;
            break;
        case UART1:
            ptr = UART1_BASE_PTR;
            break;
        case UART2:
            ptr = UART2_BASE_PTR;
            break;
    }

    return ptr;
}