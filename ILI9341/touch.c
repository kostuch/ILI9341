/*
 * touch.c
 *
 * Created: 2017-02-07 16:05:17
 *  Author: potocki
 */

#include <avr/io.h>
#include <util/delay.h>
#include "touch.h"
#include "ILI9341.h"
#include "SPI.h"

static inline void XPT2046_activate(void);
static inline void XPT2046_deactivate(void);

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
#if USE_TOUCH_CS == 1														// If TOUCH_CS in use
    TOUCH_CS_LO;
#endif
}

static inline void XPT2046_deactivate(void)
{
#if USE_TOUCH_CS == 1														// If TOUCH_CS in use
    TOUCH_CS_HI;
#endif
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

void XPT2046_rd_x(void)
{
    XPT2046_activate();
    XPT2046_wr_cmd(START_BIT | X_POS | PD_MODE3);							// Start conversion for X (default 12 bit, DFR mode)
    touch_xyz.touch_x = XPT2046_rd_data(0);
    touch_xyz.touch_x <<= 8;
    touch_xyz.touch_x |= XPT2046_rd_data(0);
    XPT2046_deactivate();
}

void XPT2046_rd_y(void)
{
	XPT2046_activate();
	XPT2046_wr_cmd(START_BIT | Y_POS | PD_MODE3);							// Start conversion for X (default 12 bit, DFR mode)
	touch_xyz.touch_y = XPT2046_rd_data(0);
	touch_xyz.touch_y <<= 8;
	touch_xyz.touch_y |= XPT2046_rd_data(0);
	XPT2046_deactivate();
}

void XPT2046_rd_z1(void)
{
	XPT2046_activate();
	XPT2046_wr_cmd(START_BIT | Z1_POS | PD_MODE3);							// Start conversion for X (default 12 bit, DFR mode)
	touch_xyz.touch_z1 = XPT2046_rd_data(0);
	touch_xyz.touch_z1 <<= 8;
	touch_xyz.touch_z1 |= XPT2046_rd_data(0);
	XPT2046_deactivate();
}

void XPT2046_rd_z2(void)
{
	XPT2046_activate();
	XPT2046_wr_cmd(START_BIT | Z2_POS | PD_MODE3);							// Start conversion for X (default 12 bit, DFR mode)
	touch_xyz.touch_z2 = XPT2046_rd_data(0);
	touch_xyz.touch_z2 <<= 8;
	touch_xyz.touch_z2 |= XPT2046_rd_data(0);
	XPT2046_deactivate();
}

void XPT2046_rd_xyz(void)
{
    XPT2046_activate();
    XPT2046_wr_cmd(START_BIT | Z1_POS | PD_MODE1);
    touch_xyz.touch_z1 = XPT2046_rd_data(0);
    touch_xyz.touch_z1 <<= 8;
    touch_xyz.touch_z1 |= XPT2046_rd_data(0);
    XPT2046_wr_cmd(START_BIT | Z2_POS | PD_MODE1);
    touch_xyz.touch_z2 = XPT2046_rd_data(0);
    touch_xyz.touch_z2 <<= 8;
    touch_xyz.touch_z2 |= XPT2046_rd_data(0);
	XPT2046_wr_cmd(START_BIT | X_POS | PD_MODE1);							// Start conversion for X (default 12 bit, DFR mode)
    touch_xyz.touch_x = XPT2046_rd_data(0);
    touch_xyz.touch_x <<= 8;
    touch_xyz.touch_x |= XPT2046_rd_data(0);
    XPT2046_wr_cmd(START_BIT | Y_POS | PD_MODE1);
    touch_xyz.touch_y = XPT2046_rd_data(0);
    touch_xyz.touch_y <<= 8;
    touch_xyz.touch_y |= XPT2046_rd_data(0);
    
    if ((rotation == LANDSCAPE) || (rotation == LANDSCAPE_REV)) swap(touch_xyz.touch_x, touch_xyz.touch_y);

    XPT2046_deactivate();
	// z2/z1=32000/400=80
	// z2/z1=14000/1500=9 (lewy gorny)
	// z2/z1=25000/3500=7 (prawy gorny)
	// z2/z1=20000/5000=4 (srodek)
	// z2/z1=18000/6000=3 (lewy dolny)
	// z2/z1=30000/11000=3 (prawy dolny)
}

void XPT2046_rd_batt(void)
{
    XPT2046_activate();
	XPT2046_wr_cmd(START_BIT | BAT_MONITOR | SER_MODE | PD_MODE1);			// Start conversion for battery (default 12 bit, SER mode)
    touch_xyz.touch_batt = XPT2046_rd_data(0);
    touch_xyz.touch_batt <<= 8;
    touch_xyz.touch_batt  |= XPT2046_rd_data(0);
	XPT2046_deactivate();
}

uint8_t touch_available(void)
{
    //return !(PIN & _BV(TOUCH_PENIRQ));
    return 0;
};

/*

 bool XPT2046_Touchscreen::bufferEmpty()
 {
	 return ((millis() - msraw) < MSEC_THRESHOLD);
 }

 static int16_t besttwoavg( int16_t x , int16_t y , int16_t z ) {
	 int16_t da, db, dc;
	 int16_t reta = 0;
	 if ( x > y ) da = x - y; else da = y - x;
	 if ( x > z ) db = x - z; else db = z - x;
	 if ( z > y ) dc = z - y; else dc = y - z;

	 if ( da <= db && da <= dc ) reta = (x + y) >> 1;
	 else if ( db <= da && db <= dc ) reta = (x + z) >> 1;
	 else reta = (y + z) >> 1;   //    else if ( dc <= da && dc <= db ) reta = (x + y) >> 1;

	 return (reta);
 }

 // TODO: perhaps a future version should offer an option for more oversampling,
 //       with the RANSAC algorithm https://en.wikipedia.org/wiki/RANSAC

 void XPT2046_Touchscreen::update()
 {
	 int16_t data[6];

	 if (!isrWake) return;
	 uint32_t now = millis();
	 if (now - msraw < MSEC_THRESHOLD) return;

	 SPI.beginTransaction(SPI_SETTING);
	 digitalWrite(csPin, LOW);
	 SPI.transfer(0xB1 ); //z1
	 int16_t z1 = SPI.transfer16(0xC1 ) >> 3; //z2
	 int z = z1 + 4095;
	 int16_t z2 = SPI.transfer16(0x91 ) >> 3; //x
	 z -= z2;
	 if (z >= Z_THRESHOLD) {
		 SPI.transfer16(0x91 );  // dummy X measure, 1st is always noisy
		 data[0] = SPI.transfer16(0xD1 ) >> 3; //y
		 data[1] = SPI.transfer16(0x91 ) >> 3; // make 3 x-y measurements
		 data[2] = SPI.transfer16(0xD1 ) >> 3;
		 data[3] = SPI.transfer16(0x91 ) >> 3;
	 }
	 else data[0] = data[1] = data[2] = data[3] = 0;	// Compiler warns these values may be used unset on early exit.
	 data[4] = SPI.transfer16(0xD0 ) >> 3;	// Last Y touch power down
	 data[5] = SPI.transfer16(0) >> 3;
	 digitalWrite(csPin, HIGH);
	 SPI.endTransaction();
	 //Serial.printf("z=%d  ::  z1=%d,  z2=%d  ", z, z1, z2);
	 if (z < 0) z = 0;
	 if (z < Z_THRESHOLD) { //	if ( !touched ) {
		 // Serial.println();
		 zraw = 0;
		 if (z < Z_THRESHOLD_INT) { //	if ( !touched ) {
			 if (255 != tirqPin) isrWake = false;
		 }
		 return;
	 }
	 zraw = z;

	 // Average pair with least distance between each measured x then y
	 //Serial.printf("    z1=%d,z2=%d  ", z1, z2);
	 //Serial.printf("p=%d,  %d,%d  %d,%d  %d,%d", zraw,
	 //data[0], data[1], data[2], data[3], data[4], data[5]);
	 int16_t x = besttwoavg( data[0], data[2], data[4] );
	 int16_t y = besttwoavg( data[1], data[3], data[5] );

	 //Serial.printf("    %d,%d", x, y);
	 //Serial.println();
	 if (z >= Z_THRESHOLD) {
		 msraw = now;	// good read completed, set wait
		 xraw = x;
		 yraw = y;
	 }
 }
 */