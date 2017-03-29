#include <avr/io.h>
#include <avr/pgmspace.h>
#include "controls.h"
#include "colors.h"
//#include "ILI9341.h"
//#include "font8x8.h"

button_t buttons[] =
{
{0, 0, 160, 20, GREEN, LIGHTGREEN, BLACK, "Load file", button_load},
{159, 0, 160, 20, GREEN, LIGHTGREEN, BLACK, "Save file", button_save}
};

/*
void draw_buttons(void)
{
	for (uint8_t i = 0; i < sizeof(buttons); i++)
	{
		ILI9341_draw_fast_rect(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, true, buttons[i].idle_color);
		ILI9341_set_font((font_t) {font8x8, 8, 8, buttons[i].text_color, buttons[i].idle_color});
		ILI9341_txt(buttons[i].x, buttons[i].y, buttons[i].text);
	}
}

void button_press(uint16_t x_click, uint16_t y_click)
{
	uint8_t i = 0;
	do 
	{
		if ((buttons[i].x < x_click) & (buttons[i].y < y_click))
		{
			ILI9341_draw_fast_rect(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, true, buttons[i].active_color);
			buttons[i].button_func();
			return;
		}
	} while (i < sizeof(buttons));
}
*/
void button_load(void)
{
	;
}

void button_save(void)
{
	;
}
