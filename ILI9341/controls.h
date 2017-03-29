#ifndef CONTROLS_H_
#define CONTROLS_H_

typedef struct button
{
	uint16_t x;
	uint16_t y;
	uint8_t width;
	uint8_t height;
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

#endif /* CONTROLS_H_ */