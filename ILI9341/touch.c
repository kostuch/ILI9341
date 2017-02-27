/*
 * touch.c
 *
 * Created: 2017-02-07 16:05:17
 *  Author: potocki
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "touch.h"
#include "ILI9341.h"
#include "SPI.h"

static inline void XPT2046_activate(void);
static inline void XPT2046_deactivate(void);

cal_t EEMEM ee_touch_cal;

void XPT2046_init_io(void)
{
    // This is already done in TFT section
    //TOUCH_MOSI_DIR |= TOUCH_MOSI;											// TFT_MOSI pin as output
    //TOUCH_SCK_DIR |= TOUCH_SCK;											// TFT_SCK pin as output
    //TOUCH_MOSI_PORT |= TOUCH_MOSI;										// Hi state
    //TOUCH_SCK_PORT |= TOUCH_SCK;
#if USE_TOUCH_CS == 1														// If TFT_CS in use
    TOUCH_CS_DIR |= TOUCH_CS;
    TOUCH_CS_PORT |= TOUCH_CS;
#endif
    TOUCH_IRQ_DIR &= ~TOUCH_IRQ;											// Input
    TOUCH_IRQ_PORT |= TOUCH_IRQ;											// Pullup
};

static inline void XPT2046_activate(void)
{
    SPCR |= (1 << SPR0);														// F_CPU/8
#if USE_TOUCH_CS == 1														// If TOUCH_CS in use
    TOUCH_CS_LO;
#endif
}

static inline void XPT2046_deactivate(void)
{
#if USE_TOUCH_CS == 1														// If TOUCH_CS in use
    TOUCH_CS_HI;
#endif
    SPCR &= ~(1 << SPR0);														// F_CPU/2
}

void XPT2046_wr_cmd(uint8_t tx)
{
    SPI_write(tx, TOUCH);
}

uint8_t XPT2046_rd_data(uint8_t tx)
{
    uint8_t rx = SPI_rxtx(tx, TOUCH);
    return rx;
}

void XPT2046_rd_touch(void)
{
    /*
     * z1=3, z2=57	19			z1=6, z2=115 19
     *				z1=20,z2=80 4.0
     * z1=25, z2=70	2.8			z1=43, z2=118 2.7
     */
	uint16_t temp;
    XPT2046_activate();
	XPT2046_wr_cmd(START_BIT | Z1_POS | MODE_8BIT | PD_MODE1);				// Start conversion for Z1 (8 bit, DFR mode)
	touch.z1 = XPT2046_rd_data(0);
	XPT2046_wr_cmd(START_BIT | Z2_POS | MODE_8BIT | PD_MODE1);				// Start conversion for Z2 (8 bit, DFR mode)
	touch.z2 = XPT2046_rd_data(0);
	
    if ((touch.z2 / (touch.z1 + 1)) < TOUCH_THRESHOLD)
    {
        for (uint8_t avg = 0; avg < TOUCH_AVG; avg++)
        {
            XPT2046_wr_cmd(START_BIT | X_POS | PD_MODE1);					// Start conversion for X (default 12 bit, DFR mode)
            temp = XPT2046_rd_data(0);
            temp <<= 8;
            temp |= XPT2046_rd_data(0);
            temp /= X_MAX / TFT_HEIGHT;
            touch.x *= TOUCH_FILTER;
            touch.x += temp;
            touch.x /= (TOUCH_FILTER + 1);
            XPT2046_wr_cmd(START_BIT | Y_POS | PD_MODE1);					// Start conversion for Y (default 12 bit, DFR mode)
            temp = XPT2046_rd_data(0);
            temp <<= 8;
            temp |= XPT2046_rd_data(0);
            temp /= Y_MAX / TFT_WIDTH;
            touch.y *= TOUCH_FILTER;
            touch.y += temp;
            touch.y /= (TOUCH_FILTER + 1);
        }

        if ((rotation == LANDSCAPE) || (rotation == LANDSCAPE_REV)) swap(touch.x, touch.y);

        if (rotation == LANDSCAPE_REV)
        {
            touch.x = TFT_WIDTH - touch.x;
            touch.y = TFT_HEIGHT - touch.y;
        }

        if (rotation == PORTRAIT) touch.x = TFT_HEIGHT - touch.x;

        if (rotation == PORTRAIT_REV) touch.y = TFT_WIDTH - touch.y;

        //if (X_CAL > 128) touch.x += X_CAL - 128;					// Add/Substract X calibration value
        //else touch.x -= 128 - X_CAL;

        //if (Y_CAL > 128) touch.y += Y_CAL - 128;					// Add/Substract Y calibration value
        //else touch.y -= 128 - Y_CAL;
    }
    else																	// not touched - dummy XY values
    {
        touch.x = -1;
        touch.y = -1;
    }
	//xy_cal();																// Apply calibration values
    XPT2046_deactivate();
}

void XPT2046_rd_batt(void)
{
    XPT2046_activate();
    XPT2046_wr_cmd(START_BIT | BAT_MONITOR | SER_MODE | PD_MODE1);			// Start conversion for battery (default 12 bit, SER mode)
    touch.v = XPT2046_rd_data(0);
    touch.v <<= 8;
    touch.v |= XPT2046_rd_data(0);
    XPT2046_deactivate();
}

void XPT2046_rd_ee_cal(void)
{
	eeprom_read_block(&touch_cal, &ee_touch_cal, sizeof(cal_t));
}

void XPT2046_wr_ee_cal(void)
{
	eeprom_write_block(&touch_cal, &ee_touch_cal, sizeof(cal_t));
}

void xy_cal(void)
{
	if ((touch.x > T_H2) && (touch.x < T_W2))								// First quater?
	{
		touch.x += ((touch.x - 120) / 120) * ((160 - touch.y) / 160) * touch_cal.xc1;
		touch.y += ((touch.x - 120) / 120) * ((160 - touch.y) / 160) * touch_cal.yc1;
	} 
	else
	{
		if ((touch.x > T_H2) && (touch.x < T_W2))							// Second quater?
		{
			touch.x += ((touch.x - 120) / 120) * ((touch.y - 160) / 160) * touch_cal.xc2;
			touch.y += ((touch.x - 120) / 120) * ((touch.y - 160) / 160) * touch_cal.yc2;
		}
		else
		{
			if ((touch.x < T_H2) && (touch.x > T_W2))						// Third quater?
			{
				touch.x += ((120 - touch.x) / 120) * ((touch.y - 160) / 160) * touch_cal.xc3;
				touch.y += ((120 - touch.x) / 120) * ((touch.y - 160) / 160) * touch_cal.yc3;
			}
			else															// Fourth quater
			{
				touch.x += ((120 - touch.x) / 120) * ((160 - touch.y) / 160) * touch_cal.xc4;
				touch.y += ((120 - touch.x) / 120) * ((160 - touch.y) / 160) * touch_cal.yc4;
			}
		}
	}
}