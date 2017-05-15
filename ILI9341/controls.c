/*
 * controls.c
 *
 *  Author: kostuch@skeletondevices.com
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "controls.h"
#include "colors.h"

button_t buttons[] =
{
{0, 0, 160, 20, true, GREEN, LIGHTGREEN, BLACK, "Load file", button_load},
{159, 0, 160, 20, true, GREEN, LIGHTGREEN, BLACK, "Save file", button_save}
};

void draw_buttons(void)
{
	for (uint8_t i = 0; i < sizeof(buttons); i++)
	{
		// Draw all defined buttons here (as not clicked) TODO
	}
}

void button_press(uint16_t x_click, uint16_t y_click)
{
	uint8_t i = 0;
	do 
	{
		if ((buttons[i].x < x_click) & (buttons[i].y < y_click))			// Clicked button? FIXME!
		{
			// Draw button in active color TODO
			buttons[i].button_func();										// Run associated function
			return;
		}
	} while (i < sizeof(buttons));
}

void button_load(void)
{
	// TODO
	;
}

void button_save(void)
{
	// TODO
	;
}

