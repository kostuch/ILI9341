/*
 * sd_card.c
 *
 * Created: 2017-03-20 15:16:03
 *  Author: potocki
 */ 

 #include <avr/io.h>
 #include "sd_card.h"

 void SDCARD_init_io(void)
 {
	 // This is already done in TFT section
	 //SDCARD_MOSI_DIR |= TOUCH_MOSI;										// SD_MOSI pin as output
	 //SDCARD_SCK_DIR |= TOUCH_SCK;											// SD_SCK pin as output
	 //SDCARD_MOSI_PORT |= TOUCH_MOSI;										// Hi state
	 //SDCARD_SCK_PORT |= TOUCH_SCK;
	 #if USE_SDCARD_CS == 1													// If TFT_CS in use
	 SD_CS_DIR |= SD_CS;
	 SD_CS_PORT |= SD_CS;
	 #endif
 };
