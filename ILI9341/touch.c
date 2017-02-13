/*
 * touch.c
 *
 * Created: 2017-02-07 16:05:17
 *  Author: potocki
 */ 

#include <avr/io.h>
#include "touch.h"

#define nop()  asm volatile("nop")

void touch_init(void) {
    TOUCH_MOSI_DIR |= TOUCH_MOSI;														// TFT_MOSI pin as output
    TOUCH_SCK_DIR |= TOUCH_SCK;															// TFT_SCK pin as output
    TOUCH_MOSI_PORT |= TOUCH_MOSI;														// Hi state
    TOUCH_SCK_PORT |= TOUCH_SCK;
    TOUCH_SCK_DIR |= TOUCH_CS;
    TOUCH_CS_PORT |= TOUCH_CS;
};

void touch_write_data(uint8_t data) {
   for (uint8_t i = 0x80; i; i >>= 1)										// 8 bits (from MSB)
   {
	   TOUCH_SCK_LO;																// Clock LOW

	   if (data & i) TOUCH_MOSI_HI;												// If bit=1, set line
	   else TOUCH_MOSI_LO;														// If bit=0, reset line

	   
   }
}

uint16_t touch_read_data(void) {
	uint16_t data = 0;

	for(uint_fast8_t count = 12; count; --count)
	{
		TOUCH_SCK_LO;																// Clock LOW
		nop(); nop(); nop();
		TOUCH_SCK_HI;																// Clock HIGH
		nop(); nop(); nop();

		if (TOUCH_MISO) data |= 1;

		data <<= 1;
	}

	return data;
}

void touch_read(uint16_t * out_x, uint16_t * out_y) {
	int temp_x, temp_y;
	int32_t tx = 0, ty = 0;

	int_fast8_t datacount = 0;

	for (uint_fast8_t i = 10; i; --i) {
		touch_write_data(0x90);

		TOUCH_SCK_LO;																// Clock LOW
		nop(); nop(); nop();
		TOUCH_SCK_HI;																// Clock HIGH
		nop(); nop(); nop();

		temp_x = touch_read_data();

		touch_write_data(0xD0);
		TOUCH_SCK_LO;																// Clock LOW
		nop(); nop(); nop();
		TOUCH_SCK_HI;																// Clock HIGH
		nop(); nop(); nop();

		temp_y = touch_read_data();

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


	if (datacount) {
		tx /= datacount;
		ty /= datacount;

		// TODO: move all these to constants. I'm just being super hacky atm
		tx -= 0x1A0;
		ty -= 0x2A3;

		tx *= 240;
		tx /= (0x1F10 - 0x01A0);

		ty *= 320;
		ty /= (0x1EE6 - 0x02A3);

		if (tx < 0) {
			tx = 0;
			} else if (tx > 239) {
			tx = 239;
		}

		if (ty < 0) {
			ty = 0;
			} else if (ty > 319) {
			ty = 319;
		}

		//  *out_x = tx;
		//  *out_y = 320-ty;
		*out_y = tx;
		*out_x = ty;
		} else {
		*out_x = *out_y = 0xFFFF;
	}
}

uint8_t touch_available(void) {
	//return !(PIN & _BV(TOUCH_PENIRQ));
	return 0;
};


/*
     #include <avr/io.h>
    #include "../SPI/spi.h"
    #include "touch.h"
    #include "../MK_SSD1963/MK_SSD1963.h"
     
    unsigned int XY_POS[2]={0,0};
     
    void TouchInit(void)
    {
            InitSpi();
            Touch_res();
            DDRB |= (1<<TOUCH_CS);
            DDRB &= ~(1<<TOUCH_INT);        //PE4 connect to Touch screen interrupt
     
    }
     
    void Touch_set(void)
    {
            //SCLK = Fosc/64
            //---SPCR |= (1<<SPR1) | (1<<SPR0) | (1<<CPHA);
            SPCR |= (1<<SPR1) | (1<<SPR0);
            SPSR |= (1<<SPI2X);
            //asm("nop");
     
    }
  
    unsigned int GetTouchADvalue(unsigned char CMD)
    {
            unsigned char spi_data;
            unsigned int ad_value = 0;
            Touch_cs();             //Ć¬Ńˇ
    //      spi_data = spiTransferByte(CMD);
            spi_data=Spi_kan_1(CMD);
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
            asm("nop");
     
            //ad_value = spi_send(0x00);
            ad_value = Spi_kan_1(0x00);
            //ad_value |= spi_data;
            //ad_value <<= 8;
            //spi_data = spi_send(0x00);
            spi_data = Spi_kan_1(0x00);
            ad_value <<= 8;
            ad_value |= spi_data;
            Touch_res();    //ĘÍ·Ĺ
            ad_value >>= 3;
            return ad_value;
    }
  
    void Touch_XY(unsigned int *pxy)
    {
            asm("nop");
            asm("nop");
            asm("nop");
     
    }
  
    void DisplayPosition(unsigned int x, unsigned int y, unsigned int Pos)
    {
            unsigned int temp;
            unsigned char i;
            temp = Pos;
            i = temp/1000;
    //      DrawAscii(x,y,(i+0x30),BLUE,WHITE, NORMAL);
            tft_putint(x,y, i, yellow, black);
            temp = temp % 1000;
            i = temp/100;
    //      DrawAscii(x+8,y,(i+0x30),BLUE,WHITE, NORMAL);
            tft_putint(x+8,y, i, yellow, black);
            temp = temp % 100;
            i = temp/10;
    //      DrawAscii(x+16,y,(i+0x30),BLUE,WHITE, NORMAL);
            tft_putint(x+16,y, i, yellow, black);
            temp = temp % 10;
            i = temp;
    //      DrawAscii(x+24,y,(i+0x30),BLUE,WHITE, NORMAL);
            tft_putint(x+24,y, i, yellow, black);
    }
*/