/*
 * controls.h
 *
 *  Author: kostuch@skeletondevices.com
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <stdbool.h>

// Button parameters
typedef struct button
{
	uint16_t x;
	uint16_t y;
	uint8_t width;
	uint8_t height;
	bool	enabled;
	uint16_t idle_color;
	uint16_t active_color;
	uint16_t text_color;
	char *text;
	void (*button_func)(void);
} button_t;

extern button_t buttons[];

void button_press(uint16_t x_click, uint16_t y_click);
void draw_buttons(void);
void button_load(void);
void button_save(void);

typedef int (*test)(uint8_t);
test funkcja(uint8_t x);

#endif /* CONTROLS_H_ */