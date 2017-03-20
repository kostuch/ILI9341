/*
 * sd_card.h
 *
 * Created: 2017-02-10 19:17:07
 *  Author: potocki
 */ 


#ifndef SD_CARD_H_
#define SD_CARD_H_

#define	USE_SDCARD_CS	1
#define SD_CS		(1<<5)													// CS
#define SD_CS_PORT	PORTD
#define SD_CS_DIR	DDRD
#define	SD_CS_PIN	PIND

#define SD_CS_LO	SD_CS_PORT &= ~SD_CS									// CS=low
#define SD_CS_HI	SD_CS_PORT |= SD_CS										// CS=high
#define	SD_CS_X		SD_CS_PIN & SD_CS										// CS state

void SDCARD_init_io(void);

#endif /* SD_CARD_H_ */