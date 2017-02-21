/*
 * touch.h
 *
 * Created: 2017-02-07 16:01:25
 *  Author: potocki
 */ 


#ifndef TOUCH_H_
#define TOUCH_H_

#define USE_TOUCH_CS	1
#define USE_PENIRQ		1
#define TOUCH_HARD_SPI

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

// definicje pinow
#define		TOUCH_SCK	(1<<5)												// CLK
#define 	TOUCH_MISO	(1<<4)												// MISO
#define 	TOUCH_MOSI	(1<<3)												// MOSI
#define 	TOUCH_IRQ	(1<<5)												// PENIRQ
#define 	TOUCH_CS	(1<<6)												// CS

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

void Touch_init(void);
void touch_wr_cmd(uint8_t cmd);
uint16_t touch_rd_data(void);

void touch_set(void);
unsigned int get_touch_value(unsigned char CMD);
void touch_xy(unsigned int *pxy);
void display_position(unsigned int x, unsigned int y, unsigned int Pos);

#endif /* TOUCH_H_ */