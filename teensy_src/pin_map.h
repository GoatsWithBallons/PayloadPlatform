/****************************************************************************************
 *
 * File:
 * 		pin_map.h
 *
 * Purpose:
 * 		Provides helpful pin definitins
 *
 *
 ***************************************************************************************/


#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEENSY_PIN_MAP_H
#define TEENSY_PIN_MAP_H


#include "gpio.h"

/* UART */
#define RX1		0
#define TX1		1
#define RX2		9
#define TX2		10
#define RX3		7
#define TX3		8

/* SPI */
#define SPI_SCK		14
#define SPI_DOUT 	11
#define SPI_DIN		12

#define SPI_CS0		10
#define SPI_CS1		9
#define SPI_CS2		20
#define SPI_CS3		21
#define SPI_CS4		15

/* PWM */
#define PWM0		3		/* Currently not supported */
#define PWM1		4		/* Currently not supported */
#define PWM2		5
#define PWM3		6
#define PWM4		22
#define PWM5		23

#endif

#ifdef __cplusplus
}
#endif