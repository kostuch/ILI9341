/*
 * touch.c
 *
 * Created: 2017-02-07 16:05:17
 *  Author: potocki
 */

#include <avr/io.h>
#include "touch.h"
#include "ILI9341.h"

#define nop()  asm volatile("nop")

void Touch_init(void)
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

void touch_wr_cmd(uint8_t cmd)
{
#ifdef TOUCH_HARD_SPI
    SPDR = cmd;

    while (!(SPSR & (1 << SPIF)));											// Wait for transmission complete

#else

    for (uint8_t i = 0x80; i; i >>= 1)										// 8 bits (from MSB)
    {
        TOUCH_SCK_LO;														// Clock LOW

        if (cmd & i) TOUCH_MOSI_HI;										// If bit=1, set line
        else TOUCH_MOSI_LO;													// If bit=0, reset line
    }

#endif
}

uint16_t touch_rd_data(void)
{
#ifdef TOUCH_HARD_SPI
    uint16_t position;
    //position = SPI_rxtx(START_BIT | Z1_POS);								// Pressure 1
    while (!(SPSR & (1 << SPIF))) ;											// Wait for reception complete

	SPDR = (START_BIT | Z2_POS);											// Pressure 2
    position = SPDR;														// First 7 bits
    SPDR = 0xFF;															// Dummy byte
    position <<= 7;

    while (!(SPSR & (1 << SPIF))) ;											// Wait for reception complete

    position |= SPDR;														// Remaining bits
    return position;
#else
    uint16_t position = 0;

    for (uint8_t count = 12; count; --count)
    {
        TOUCH_SCK_LO;																// Clock LOW
        TOUCH_SCK_HI;																// Clock HIGH

        if (TOUCH_MISO) position |= 1;

        position <<= 1;
    }

    return position;
#endif
}

void touch_read(uint16_t *out_x, uint16_t *out_y)
{
    int temp_x, temp_y;
    int32_t tx = 0, ty = 0;
    uint8_t datacount = 0;

    for (uint_fast8_t i = 10; i; --i)
    {
        touch_wr_cmd(0x90);
        TOUCH_SCK_LO;																// Clock LOW
        nop(); nop(); nop();
        TOUCH_SCK_HI;																// Clock HIGH
        nop(); nop(); nop();
        temp_x = touch_rd_data();
        touch_wr_cmd(0xD0);
        TOUCH_SCK_LO;																// Clock LOW
        nop(); nop(); nop();
        TOUCH_SCK_HI;																// Clock HIGH
        nop(); nop(); nop();
        temp_y = touch_rd_data();

        if (temp_x && temp_y
                // && (temp_x > 0x01A0)
                && (temp_x < 0x1F10)
                //   && (temp_y > 0x02A3)
                && (temp_y < 0x1EE6)
           )
        {
            ty += temp_x;
            tx += temp_y;
            ++datacount;
        }
    }

    if (datacount)
    {
        tx /= datacount;
        ty /= datacount;
        // TODO: move all these to constants. I'm just being super hacky atm
        tx -= 0x1A0;
        ty -= 0x2A3;
        tx *= 240;
        tx /= (0x1F10 - 0x01A0);
        ty *= 320;
        ty /= (0x1EE6 - 0x02A3);

        if (tx < 0)
        {
            tx = 0;
        }
        else if (tx > 239)
        {
            tx = 239;
        }

        if (ty < 0)
        {
            ty = 0;
        }
        else if (ty > 319)
        {
            ty = 319;
        }

        //  *out_x = tx;
        //  *out_y = 320-ty;
        *out_y = tx;
        *out_x = ty;
    }
    else
    {
        *out_x = *out_y = 0xFFFF;
    }
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