/*
 * ILI9341.c
 *
 * Created: 2017-02-07 10:15:12
 * Author : kostuch@skeletondevices.com
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "ILI9341.h"
#include "colors.h"
#include "fonts5x7.h"
#include "font16x16.h"
#include "bmp_mono.h"
#include "bmp_color.h"

int main(void)
{
    ILI9341_init();															// Inicjalizacja
	ILI9341_set_rotation(LANDSCAPE_REV);									// Landscape odwrocony
	
	ILI9341_cls(BLUE);														// Ekran na niebiesko
	
	for (uint8_t i=0; i<100; i+=3)											// Zolta przerywana linia
	{
		ILI9341_draw_pixel(i, 100, YELLOW);
	}
	_delay_ms(500);

	ILI9341_draw_line(10, 10, 200, 100, RED);								// Swobodna linia
    _delay_ms(500);
		
	ILI9341_set_font((font_t) {font5x7, 5, 7, YELLOW, TRANSPARENT});		// font "systemowy" transparentny
	ILI9341_txt(0, 0, "Tekst fontem systemowym");
	ILI9341_set_font((font_t) {font5x7, 5, 7, YELLOW, BLACK});				// font "systemowy"
	ILI9341_chr(200, 0, '#');
	ILI9341_set_font((font_t) {font16x16, 16, 16, RED, TRANSPARENT});		// font 16x16 transparentny
	ILI9341_txt(0, 50, "Tekst trans");
	ILI9341_set_font((font_t) {font16x16, 16, 16, RED, GREEN});				// font 16x16 
	ILI9341_txt(0, 70, "Tekst solid");
	
	ILI9341_draw_mono_bmp(120, 100, 60, 60, gps_mono, WHITE, GRAYBLUE);		// Dwukolorowa bitmapa
	
	ILI9341_draw_mono_trans_bmp(120, 170, 60, 60, gps_mono, YELLOW);		// Przezroczysta bitmapa
	
	ILI9341_draw_circle(100, 100, 50, false, WHITE);						// Okrag
	ILI9341_draw_circle(200, 100, 50, true, GRAY);							// Kolo
	
	    uint16_t kwadrat[4][2] =
	    {
		    {60, 60},
		    {160, 60},
		    {160, 160},
		    {60, 160}
	    };

	ILI9341_draw_polygon(*kwadrat, 3, RED, 1);								// Zamkniety kwadrat
	ILI9341_draw_triangle(0, 0, 250, 200, 100, 150, BLACK);					// Trojkat
	ILI9341_draw_rectangle(10, 10, 200, 200, MAGENTA);						// Prostokat

	ILI9341_draw_color_bmp(240, 200, 32, 32, suzuki);						// Bitmapa kolorowa

	while (1)
    {
    }
}

