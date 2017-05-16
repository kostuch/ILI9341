/*
 * controls.h
 *
 *  Author: kostuch@skeletondevices.com
 */

#ifndef CONTROLS_H_
#define CONTROLS_H_

// Button parameters
typedef struct button
{
	uint16_t x;																// Left Upper
	uint16_t y;																// Corner
	uint8_t width;															// Size
	uint8_t height;
	uint16_t idle_color;
	uint16_t active_color;
	uint16_t text_color;
	const char *text;														// Caption
	void (*button_func)(void);												// Associated function
	//uint8_t * btn_flags;
} button_t;

enum buttons {btn_load_file = 0, btn_save_file = 1, btn_caltft = 2,
              btn_save_cal = 3, btn_menu = 4, btn_ok = 5, btn_cancel = 6,
			  btn_up = 7, btn_dn = 8, btn_dot = 9,
			  btn_0 = 10, btn_1 = 11, btn_2 = 12, btn_3 = 13, btn_4 = 14,
			  btn_5 = 15, btn_6 = 16, btn_7 = 17, btn_8 = 18, btn_9 = 19
             };

const button_t buttons[3];

void button_press(uint16_t x_click, uint16_t y_click);
void draw_button(enum buttons);
void btn_load(void);
void btn_save(void);
void btn_calibrate_tft(void);

typedef int (*test)(uint8_t);
test funkcja(uint8_t x);

#endif /* CONTROLS_H_ */