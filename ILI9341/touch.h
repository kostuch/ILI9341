/*
 * touch.h
 *
 * Created: 2017-02-07 16:01:25
 *  Author: potocki
 */ 

#include <avr/eeprom.h>
#include <stdbool.h>

#ifndef TOUCH_H_
#define TOUCH_H_

#define USE_TOUCH_CS	1
#define USE_PENIRQ		1

#define T_HEIGHT		240
#define T_WIDTH			320
#define T_H2			(T_HEIGHT / 2)
#define T_W2			(T_WIDTH / 2)

#define START_BIT       0x80
#define MODE_12BIT      0x00
#define MODE_8BIT       0x08
#define SER_MODE        0x04
#define DFR_MODE        0x00

#define PD_MODE0        0x00												//PENIRQ Enabled,Power-Down Between Conversions.
#define PD_MODE1        0x01												//PENIRQ Disabled,Reference is off and ADC is on.
#define PD_MODE2        0x02												//PENIRQ Enabled,Reference is on and ADC is off.
#define PD_MODE3        0x03												//PENIRQ Disabled,Device is always powered.

#define TEMP0           0x00
#define TEMP1           0x70
#define BAT_MONITOR     0x20
#define AUX_IN          0x60
#define Y_POS           0x10
#define X_POS           0x50
#define Z1_POS          0x30
#define Z2_POS          0x40

#define X_MAX			30000
#define Y_MAX			30000
#define X_SCALE			125													// 30000/240=125
#define Y_SCALE			94													// 30000/320=94
#define TOUCH_AVG		10													// Number of touch samples to avg
#define TOUCH_FILTER	2													// Filter touch response
#define TOUCH_THRESHOLD	700													// Y*(Z2/(Z1+1))
#define MAX_CAL_ERROR	10													// Max difference at calibration moment
#define X_CAL			118													// value>128 -> add
#define Y_CAL			108													// value<128 -> substract
#define	swap(a, b)		{uint16_t t = a ; a = b; b = t; }

// definicje pinow
#define		TOUCH_SCK	(1<<5)												// CLK
#define 	TOUCH_MISO	(1<<4)												// MISO
#define 	TOUCH_MOSI	(1<<3)												// MOSI
#define 	TOUCH_IRQ	(1<<5)												// PENIRQ
#define 	TOUCH_CS	(1<<7)												// CS

/*
#define		TOUCH_SCK	(1<<2)												// CLK
#define 	TOUCH_MISO	(1<<3)												// MISO
#define 	TOUCH_MOSI	(1<<4)												// MOSI
#define 	TOUCH_IRQ	(1<<5)												// PENIRQ
#define 	TOUCH_CS	(1<<6)												// CS
*/

// definicje portow
#define 	TOUCH_SCK_PORT	PORTB
#define 	TOUCH_SCK_DIR	DDRB
#define 	TOUCH_MOSI_PORT	PORTB
#define 	TOUCH_MOSI_DIR	DDRB
#define 	TOUCH_MISO_PORT	PORTB
#define 	TOUCH_MISO_DIR	DDRB
#define 	TOUCH_MISO_PIN	PINB
#define 	TOUCH_CS_PORT	PORTD
#define 	TOUCH_CS_DIR	DDRD
#define 	TOUCH_IRQ_PORT	PORTD
#define 	TOUCH_IRQ_DIR	DDRD

// definicje makr
#define 	TOUCH_SCK_LO	TOUCH_SCK_PORT &= ~TOUCH_SCK
#define 	TOUCH_SCK_HI	TOUCH_SCK_PORT |= TOUCH_SCK
#define 	TOUCH_MOSI_LO	TOUCH_MOSI_PORT &= ~TOUCH_MOSI
#define 	TOUCH_MOSI_HI	TOUCH_MOSI_PORT |= TOUCH_MOSI
#define 	TOUCH_CS_LO		TOUCH_CS_PORT &= ~TOUCH_CS
#define 	TOUCH_CS_HI		TOUCH_CS_PORT |= TOUCH_CS
#define		TOUCH_MISO_X	TOUCH_MISO_PIN & TOUCH_MISO

typedef struct
{
	int16_t x;
	int16_t y;
	uint8_t z1;
	uint8_t z2;
	uint16_t v;
	bool ok;
} touch_t;

// ------------------
// | UL          UR |
// |                |
// |                |
// |                |
// |                |
// |                |
// |                |
// |                |
// | DL          DR |
// ------------------

typedef struct
{
	int8_t xc1;
	int8_t yc1;
	int8_t xc2;
	int8_t yc2;
	int8_t xc3;
	int8_t yc3;
	int8_t xc4;
	int8_t yc4;
} cal_t;

touch_t touch;
cal_t touch_cal;
extern cal_t EEMEM ee_touch_cal;

void XPT2046_init_io(void);
//void XPT2046_wr_cmd(uint8_t tx);
void XPT2046_rd_touch(void);
void XPT2046_rd_batt(void);
void XPT2046_rd_ee_cal(void);
void XPT2046_wr_ee_cal(void);
void xy_cal(void);

#endif /* TOUCH_H_ */