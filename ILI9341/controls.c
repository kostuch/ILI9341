/*
 * controls.c
 *
 *  Author: kostuch@skeletondevices.com
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "controls.h"
#include "colors.h"
#include "ILI9341.h"
#include "font8x8.h"

const button_t buttons[] PROGMEM =
{
	{0, 0, 160, 20, GREEN, LIGHTGREEN, BLACK, "Load file", btn_load},
	{159, 0, 160, 20, GREEN, LIGHTGREEN, BLACK, "Save file", btn_save},
	{40, 0, 160, 20, GREEN, LIGHTGREEN, BLACK, "Calibration", btn_calibrate_tft}
};

void draw_button(enum buttons btn)
{
	uint16_t x, y, w, h;
	x = buttons[btn].x;
	y = buttons[btn].y;
	w = buttons[btn].width;
	h = buttons[btn].height;

	//if (buttons[btn].enabled)
	{
		ILI9341_draw_fast_rect(x, y, w, h, true, buttons[btn].idle_color);
	}
	//else
	{
		ILI9341_draw_fast_rect(x, y, w, h, false, buttons[btn].idle_color);
	}

	ILI9341_set_font((font_t) {font8x8, 8, 8, buttons[btn].text_color, TRANSPARENT});
	ILI9341_txt_P(x, y, buttons[btn].text);
}

void button_press(uint16_t x_click, uint16_t y_click)
{
	uint8_t i = 0;

	do
	{
		if ((buttons[i].x < x_click) & (buttons[i].y < y_click) &
		    (buttons[i].x + buttons[i].width > x_click) &
		    (buttons[i].y + buttons[i].height > y_click))					// Clicked button?
		{
			//if (buttons[i].enabled)
			{
			// Draw button in active color TODO
			buttons[i].button_func();										// Run associated function
			}
			break;
		}
	}
	while (i < sizeof(buttons));
}

void btn_load(void)
{
	// TODO
	;
}

void btn_save(void)
{
	// TODO
	;
}

void btn_calibrate_tft(void)
{
	// TODO
	;
}

