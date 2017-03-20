/*
 * ILI9341.c
 *
 * Created: 2017-02-07 10:15:12
 * Author : kostuch@skeletondevices.com
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
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
#include "literals.h"
#include "globals.h"

void touch_calibration(void);
char driver_id_a[16];

int main(void)
{
    ILI9341_init();															// Inicjalizacja LCD
    XPT2046_init_io();														// Inicjalizacja digitizera
    XPT2046_rd_ee_cal();													// Odczyt matrycy kalibracji
    ILI9341_set_rotation(LANDSCAPE);										// Landscape
    //touch_calibration();													// KALIBRACJA dotyku
    ILI9341_cls(BLUE);														// Ekran na niebiesko
    ILI9341_set_font((font_t) {font16x16, 16, 16, YELLOW, BLUE});			// font 16x16 transparentny
    /*
    ILI9341_txt(0, 0, "Screen ID:");
    ILI9341_txt(160, 0, itoa(ILI9341_rd_id(), driver_id_a, 16));
    */

    while (1)
    {
        XPT2046_rd_touch();
        /*
        ILI9341_txt(40, 60, "      ");
        ILI9341_txt(40, 60, itoa(touch.z1, driver_id_a, 10));
        ILI9341_txt(40, 80, "      ");
        ILI9341_txt(40, 80, itoa(touch.z2, driver_id_a, 10));
        ILI9341_txt(40, 100, "      ");
        ILI9341_txt(40, 100, itoa((touch.y_raw * (touch.z2 / (touch.z1 + 1)), driver_id_a, 10));

        _delay_ms(50);
        */

        if (touch.ok)
        {
            ILI9341_draw_pixel(touch.x_cal, touch.y_cal, YELLOW);
            ILI9341_draw_pixel(touch.x_cal - 1, touch.y_cal, YELLOW);
            ILI9341_draw_pixel(touch.x_cal + 1, touch.y_cal, YELLOW);
            ILI9341_draw_pixel(touch.x_cal, touch.y_cal - 1, YELLOW);
            ILI9341_draw_pixel(touch.x_cal, touch.y_cal + 1, YELLOW);
            //ILI9341_txt(40, 60, "      ");
            //ILI9341_txt(40, 60, itoa(touch.x_cal, driver_id_a, 10));
            //ILI9341_txt(40, 80, "      ");
            //ILI9341_txt(40, 80, itoa(touch.y_cal, driver_id_a, 10));
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
        ;
}

void touch_calibration(void)
{
    ILI9341_cls(BLACK);
    ILI9341_set_font((font_t) {font16x16, 16, 16, YELLOW, BLACK});
    int32_t x, y;
    point_t sample_points[3];

    for (uint8_t cal_step = 0; cal_step < 3; cal_step++)					// Three calibration points
    {
        ILI9341_txt_P(0, 120, PGM_GETSTR(calibration_txt, cal_prompt_idx));	// Prompt
        eeprom_read_block(&x, &ee_cal_points[cal_step].x, sizeof(x));		// Read calibration points coordinates from EEPROM
        eeprom_read_block(&y, &ee_cal_points[cal_step].y, sizeof(y));
        ILI9341_draw_circle(x, y, 5, true, WHITE);							// Draw new calibration circle at this coordinates

        do
        {
            do
            {
                XPT2046_rd_touch();
            }
            while (!touch.ok);												// Wait for valid touch

            sample_points[cal_step].x = touch.x_raw;						// Get X touch coordinates
            sample_points[cal_step].y = touch.y_raw;						// Get Y touch coordinates

            if (labs(x - touch.x_raw) > MAX_CAL_ERROR || labs(y - touch.y_raw) > MAX_CAL_ERROR)
            {
                ILI9341_set_font((font_t) {font16x16, 16, 16, RED, BLACK});
                ILI9341_txt_P(0, 120, PGM_GETSTR(calibration_txt, cal_bad_idx));
            }
            else
            {
                ILI9341_set_font((font_t) {font16x16, 16, 16, GREEN, BLACK});
                ILI9341_txt_P(0, 120, PGM_GETSTR(calibration_txt, cal_ok_idx));
            }

            // DEBUG
            /*
            ILI9341_txt(40, 20, "     ");
            ILI9341_txt(40, 20, itoa(touch.y_raw * (touch.z2 / (touch.z1 + 1)), driver_id_a, 10));
            ILI9341_txt(40, 40, "     ");
            ILI9341_txt(40, 40, itoa(x, driver_id_a, 10));
            ILI9341_txt(40, 60, "     ");
            ILI9341_txt(40, 60, itoa(y, driver_id_a, 10));
            ILI9341_txt(40, 80, "     ");
            ILI9341_txt(40, 80, itoa(touch.x_raw, driver_id_a, 10));
            ILI9341_txt(40, 100, "     ");
            ILI9341_txt(40, 100, itoa(touch.y_raw, driver_id_a, 10));
            */
        }
        while (labs(x - touch.x_raw) > MAX_CAL_ERROR || labs(y - touch.y_raw) > MAX_CAL_ERROR);

        _delay_ms(500);
        ILI9341_draw_circle(x, y, 5, true, BLACK);							// Remove old calibration circle
        //  20,  20 ->  32,  31
        // 300, 120 -> 292, 131
        // 160, 220 -> 161, 223
        // A: -25776
        // B: 280
        // C: -16312
        // D: -800
        // E: -26436
        // F: 12652
        // div: -28516
    }

    set_cal_matrix(sample_points);											// Create calibration matrix
    //XPT2046_wr_ee_cal();													// Store it in EEPROM
    ILI9341_set_font((font_t) {font16x16, 16, 16, YELLOW, BLACK});
    ILI9341_txt_P(0, 120, PGM_GETSTR(calibration_txt, cal_end_idx));
}
