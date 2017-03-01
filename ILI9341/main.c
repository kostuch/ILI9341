﻿/*
 * ILI9341.c
 *
 * Created: 2017-02-07 10:15:12
 * Author : kostuch@skeletondevices.com
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ILI9341.h"
#include "colors.h"
#include "fonts5x7.h"
#include "font8x8.h"
#include "font8x12.h"
#include "font16x16.h"
#include "bmp_mono.h"
#include "bmp_color.h"
#include "touch.h"

int main(void)
{
    ILI9341_init();															// Inicjalizacja LCD
	XPT2046_init_io();														// Inicjalizacja digitizera
	XPT2046_rd_ee_cal();
    ILI9341_set_rotation(LANDSCAPE);										// Landscape
    ILI9341_cls(BLUE);														// Ekran na niebiesko
    ILI9341_set_font((font_t) {font16x16, 16, 16, YELLOW, BLUE});			// font 16x16 transparentny
    ILI9341_txt(0, 0, "Screen ID:");
    char driver_id_a[8];
	ILI9341_txt(160, 0, itoa(ILI9341_rd_id(), driver_id_a, 16));
	
	ILI9341_txt(0, 20, "X");
	ILI9341_txt(0, 40, "Y");
	ILI9341_txt(0, 60, "Z1");
	ILI9341_txt(0, 80, "Z2");
	ILI9341_txt(0, 100, "Pr");
	while (1)
	{
		XPT2046_rd_touch();
		/*
		ILI9341_txt(40, 60, "      ");
		ILI9341_txt(40, 60, itoa(touch.z1, driver_id_a, 10));
		ILI9341_txt(40, 80, "      ");
		ILI9341_txt(40, 80, itoa(touch.z2, driver_id_a, 10));
		ILI9341_txt(40, 100, "      ");
		ILI9341_txt(40, 100, itoa(touch.y * (touch.z2 / (touch.z1 + 1)), driver_id_a, 10));
		*/
		//_delay_ms(5);
		
		if (touch.ok)
		{
			ILI9341_draw_pixel(touch.x, touch.y,YELLOW);
			ILI9341_draw_pixel(touch.x - 1, touch.y,YELLOW);
			ILI9341_draw_pixel(touch.x + 1, touch.y,YELLOW);
			ILI9341_draw_pixel(touch.x, touch.y - 1,YELLOW);
			ILI9341_draw_pixel(touch.x, touch.y + 1,YELLOW);
			/*
			if (touch.y < 200)
			{
				ILI9341_txt(40, 20, "      ");
				ILI9341_txt(40, 20, itoa(touch.x, driver_id_a, 10));
				ILI9341_txt(40, 40, "      ");
				ILI9341_txt(40, 40, itoa(touch.y, driver_id_a, 10));
				ILI9341_txt(40, 60, "      ");
				ILI9341_txt(40, 60, itoa(touch.z1, driver_id_a, 10));
				ILI9341_txt(40, 80, "      ");
				ILI9341_txt(40, 80, itoa(touch.z2, driver_id_a, 10));
				ILI9341_txt(40, 100, "      ");
				ILI9341_txt(40, 100, itoa(touch.y * (touch.z2 / (touch.z1 + 1)), driver_id_a, 10));
			}
			*/
		}
		
	}

    /*
    for (uint8_t i=0; i<100; i+=3)											// Zolta przerywana linia
    {
    	ILI9341_draw_pixel(i, 100, YELLOW);
    }
    _delay_ms(500);
    */
    /*
    ILI9341_draw_line(10, 10, 200, 100, RED);								// Swobodna linia
    _delay_ms(500);
    */
    /*
    ILI9341_set_font((font_t) {font5x7, 5, 7, YELLOW, TRANSPARENT});		// font "systemowy" transparentny
    ILI9341_txt(0, 0, "Tekst fontem systemowym");
    ILI9341_set_font((font_t) {font5x7, 5, 7, YELLOW, BLACK});				// font "systemowy"
    ILI9341_chr(200, 0, '#');
    ILI9341_set_font((font_t) {font16x16, 16, 16, RED, TRANSPARENT});		// font 16x16 transparentny
    ILI9341_txt(0, 50, "Tekst trans");
    ILI9341_set_font((font_t) {font16x16, 16, 16, RED, GREEN});				// font 16x16
    ILI9341_txt(0, 70, "Tekst solid");
    */
    //ILI9341_draw_mono_bmp(120, 100, 60, 60, gps_mono, WHITE, GRAYBLUE);		// Dwukolorowa bitmapa
    //ILI9341_draw_mono_trans_bmp(120, 170, 60, 60, gps_mono, YELLOW);		// Przezroczysta bitmapa
    //ILI9341_draw_circle(100, 100, 50, false, WHITE);						// Okrag
    //ILI9341_draw_circle(200, 100, 50, true, GRAY);							// Kolo
    /*
    uint16_t kwadrat[4][2] =
    {
    	{60, 60},
    	{160, 60},
    	{160, 160},
    	{60, 160}
    };
    */
    //ILI9341_draw_polygon(*kwadrat, 3, RED, 1);								// Zamkniety kwadrat
    //ILI9341_draw_triangle(0, 0, 250, 200, 100, 150, BLACK);					// Trojkat
    //ILI9341_draw_rectangle(10, 10, 200, 200, MAGENTA);						// Prostokat
    //ILI9341_draw_color_bmp(240, 200, 32, 32, suzuki);						// Bitmapa kolorowa
    /*
    ILI9341_negative();
    _delay_ms(2000);
    ILI9341_set_8colors();
    _delay_ms(2000);
    ILI9341_negative();
    _delay_ms(2000);
    ILI9341_set_64kcolors();
    _delay_ms(2000);
    */
    /*
    ILI9341_draw_fast_line(100, 100, 100, YELLOW, HORIZONTAL);
    ILI9341_draw_fast_line(100, 100, 100, RED, VERTICAL);
    ILI9341_draw_fast_line(100, 100, 100, BLACK, UP_SLOPE);
    ILI9341_draw_fast_line(100, 100, 100, WHITE, DN_SLOPE);
    _delay_ms(500);
    */
    //ILI9341_draw_fast_rect(150, 110, 160, 120, false, MAGENTA);				// Szybki prostokat
    //ILI9341_draw_fast_rect(0, 0, 320, 240, true, BLUE);						// Szybki wypelniony prostokat (CLS)
    //ILI9341_draw_fast_rect(10, 20, 40, 50, true, YELLOW);					// Szybki wypelniony prostokat

    while (1)
    {
    }
}

