/*
 * touch.h
 *
 * Created: 2017-02-07 16:01:25
 *  Author: potocki
 */ 


#ifndef TOUCH_H_
#define TOUCH_H_


#define Start_bit       0x80
#define Mode_12bit      0x00
#define Mode_8bit       0x08
#define SER_Mode        0x04
#define DFR_Mode        0x00

#define PD_Mode0        0x00    //PENIRQ Enabled,Power-Down Between Conversions.
#define PD_Mode1        0x01    //PENIRQ Disabled,Reference is off and ADC is on.
#define PD_Mode2        0x02    //PENIRQ Enabled,Reference is on and ADC is off.
#define PD_Mode3        0x03    //PENIRQ Disabled,Device is always powered.
//Reference is on and ADC is on.
#define TEMP0           0x00
#define TEMP1           0x70
#define BAT_monitor     0x20
#define AUX_in          0x60
#define Y_POS           0x10
#define X_POS           0x50
#define Z1_POS          0x30
#define Z2_POS          0x40

// definicje pinow
#define		TOUCH_SCK	(1<<5)												// CLK
#define 	TOUCH_MOSI	(1<<4)												// MOSI
#define 	TOUCH_IRQ	(1<<2)												// PENIRQ
#define 	TOUCH_CS	(1<<1)												// CS
#define 	TOUCH_MISO	(1<<0)												// MISO

// definicje portow
#define 	TOUCH_SCK_PORT	PORTB
#define 	TOUCH_SCK_DIR	DDRB
#define 	TOUCH_MOSI_PORT	PORTB
#define 	TOUCH_MOSI_DIR	DDRB
#define 	TOUCH_MISO_PORT	PORTB
#define 	TOUCH_MISO_DIR	DDRB
#define 	TOUCH_CS_PORT	PORTB
#define 	TOUCH_CS_DIR	DDRB
#define 	TOUCH_IRQ_PORT	PORTB
#define 	TOUCH_IRQ_DIR	DDRB

// definicje makr
#define 	TOUCH_SCK_LO	TOUCH_SCK_PORT &= ~TOUCH_SCK
#define 	TOUCH_SCK_HI	TOUCH_SCK_PORT |= TOUCH_SCK
#define 	TOUCH_MOSI_LO	TOUCH_MOSI_PORT &= ~TOUCH_MOSI
#define 	TOUCH_MOSI_HI	TOUCH_MOSI_PORT |= TOUCH_MOSI
#define 	TOUCH_CS_LO		TOUCH_CS_PORT &= ~TOUCH_CS
#define 	TOUCH_CS_HI		TOUCH_CS_PORT |= TOUCH_CS

void TouchInit(void);
void Touch_set(void);
unsigned int GetTouchADvalue(unsigned char CMD);
void Touch_XY(unsigned int *pxy);
void DisplayPosition(unsigned int x, unsigned int y, unsigned int Pos);




#endif /* TOUCH_H_ */