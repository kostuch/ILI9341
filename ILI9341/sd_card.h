/*
 * sd_card.h
 *
 * Created: 2017-02-10 19:17:07
 *  Author: potocki
 */ 


#ifndef SD_CARD_H_
#define SD_CARD_H_

#define 	SD_CS		(1<<6)												// CS
#define 	SD_CS_PORT	PORTD
#define 	SD_CS_DIR	DDRD

#define 	SD_CS_LO	SD_CS_PORT &= ~SD_CS
#define 	SD_CS_HI	SD_CS_PORT |= SD_CS

#endif /* SD_CARD_H_ */