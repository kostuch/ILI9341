/*
 * SPI.c
 *
 * Created: 2017-02-21 12:55:13
 *  Author: potocki
 */
#include <avr/io.h>
#include "SPI.h"
#include "ILI9341.h"
#include "touch.h"

void SPI_init(void)
{
    PRR &= ~(1 << PRSPI);													// Enable SPI in Power Reduction Register
    SPCR = ((1 << SPE) |													// SPI Enable
            (0 << SPIE) |													// SPI Interupt Enable
            (0 << DORD) |													// Data Order (0:MSB first / 1:LSB first)
            (1 << MSTR) |													// Master/Slave select
            (0 << SPR1) | (0 << SPR0) |										// SPI Clock Rate F_CPU/4
            (0 << CPOL) |													// Clock Polarity (0:SCK low / 1:SCK hi when idle)
            (0 << CPHA));													// Clock Phase (0:leading / 1:trailing edge sampling)
    SPSR = (1 << SPI2X);													// Double Clock Rate F_CPU/2
}

/* Send byte via SPI */
void SPI_write(uint8_t tx, enum dev_t device)
{
#ifdef USE_HARD_SPI
	SPDR = tx;

    while (!(SPSR & (1 << SPIF)));											// Wait for transmission complete

#else

    for (uint8_t i = 0x80; i; i >>= 1)										// 8 bits (from MSB)
    {
        switch (device)
        {
            case TFT:
                TFT_SCK_LO;															// Clock LOW

                if (tx & i) TFT_MOSI_HI;											// If bit=1, set line
                else TFT_MOSI_LO;													// If bit=0, reset line

                TFT_SCK_HI;															// Clock HIGH
                break;

            case TOUCH:
                TOUCH_SCK_LO;															// Clock LOW

                if (tx & i) TOUCH_MOSI_HI;											// If bit=1, set line
                else TOUCH_MOSI_LO;													// If bit=0, reset line
                TOUCH_SCK_HI;															// Clock HIGH
                break;

            case SDCARD:
                break;
        }
    }

#endif
}

/* Bitbang byte via SPI */
uint8_t SPI_rxtx(uint8_t tx, enum dev_t device)
{
#ifdef USE_HARD_SPI
	SPDR = tx;																// Dummy byte

    while (!(SPSR & (1 << SPIF)));											// Wait for transmission complete

#else
	uint8_t rx;
    for (uint8_t i = 0x80; i; i >>= 1)										// 8 bits (from MSB)
    {
        switch (device)
        {
            case TFT:
				TFT_SCK_LO;													// Clock LOW
				TFT_SCK_HI;													// Clock HIGH
				rx <<= 1;													// Shift bit

				if (TFT_MISO_PIN & TFT_MISO) rx |= 0x01;					// If MISO set, then set bit
                break;

            case TOUCH:
				TOUCH_SCK_LO;												// Clock LOW
				TOUCH_SCK_HI;												// Clock HIGH
				rx <<= 1;													// Shift bit

				if (TOUCH_MISO_PIN & TOUCH_MISO) rx |= 0x01;				// If MISO set, then set bit
                break;

            case SDCARD:
                break;
        }
    }

#endif
    return SPDR;
}
