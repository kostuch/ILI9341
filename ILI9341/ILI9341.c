﻿/*
 * ILI9341.c
 *
 * Created: 2016-07-18 11:35:33
 *  Author: kostuch@skeletondevices.com
 *  Version: 0.2
 */

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ILI9341.h"
#include "colors.h"

static void ILI9341_wr_cmd(uint8_t cmd);
static void ILI9341_wr_data(uint8_t data);
static inline void ILI9341_push_color(uint16_t color);
//static uint16_t ILI9341_rd_data(void);

/* Reset LCD */
void ILI9341_reset()
{
    TFT_RST_LO;																// 10ms reset pulse (if in use)
    _delay_ms(10);
    TFT_RST_HI;
}

/* Activate via ChipSelect signal */
void ILI9341_select()
{
    TFT_CS_LO;
}

/* Deactivate via ChipSelect signal */
void ILI9341_deselect()
{
    TFT_CS_HI;
}

/* Init pins for soft SPI */
static void ILI9341_initSPI()
{
    TFT_MOSI_DIR |= TFT_MOSI;												// TFT_MOSI pin as output
    TFT_SCK_DIR |= TFT_SCK;													// TFT_SCK pin as output
    TFT_DC_DIR |= TFT_DC;													// TFT_DC pin as output
    TFT_MOSI_PORT |= TFT_MOSI;												// Hi state
    TFT_SCK_PORT |= TFT_SCK;
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_DIR |= TFT_CS;
    TFT_CS_PORT |= TFT_CS;
#endif
#if USE_TFT_RST == 1
    TFT_RST_DIR |= TFT_RST;													// TFT_RST pin as output
    TFT_RST_PORT |= TFT_RST;												// Hi state
#endif
}

/* Bitbang byte via SPI */
static void SPI_write(uint8_t data)
{
    for (uint8_t i = 0x80; i; i >>= 1)										// 8 bits (from MSB)
    {
        TFT_SCK_LO;															// Clock LOW

        if (data & i) TFT_MOSI_HI;											// If bit=1, set line
        else TFT_MOSI_LO;													// If bit=0, reset line

        TFT_SCK_HI;															// Clock HIGH
    }
}

/* Write command */
static void ILI9341_wr_cmd(uint8_t command)
{
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_HI;
#endif
    TFT_DC_LO;																// TFT_DC LOW - command
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_LO;
#endif
    SPI_write(command);														// Send byte via SPI
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_HI;
#endif
}

/* Write data */
static void ILI9341_wr_data(uint8_t data)
{
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_HI;
#endif
    TFT_DC_HI;																// TFT_DC HIGH - data
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_LO;
#endif
    SPI_write(data);														// Send byte via SPI
#if USE_TFT_CS == 1															// If TFT_CS in use
    TFT_CS_HI;
#endif
}

/* Initialisation */
void ILI9341_init()
{
    ILI9341_initSPI();
#if USE_TFT_RST == 1
    TFT_RST_HI;
    _delay_ms(50);
    TFT_RST_LO;
    _delay_ms(50);
    TFT_RST_HI;
    _delay_ms(50);
#else
    TFT_CS_HI;
    _delay_ms(25);
    TFT_CS_LO;
    _delay_ms(25);
    TFT_CS_HI;
#endif
    ILI9341_wr_cmd(ILI9341_POWER_CONTROL_A);								// ??? bez tego nie dziala
    ILI9341_wr_data(0x39);
    ILI9341_wr_data(0x2C);
    ILI9341_wr_data(0x00);
    ILI9341_wr_data(0x34);
    ILI9341_wr_data(0x02);
    ILI9341_wr_cmd(ILI9341_POWER_CONTROL_B);								// ??? bez tego nie dziala
    ILI9341_wr_data(0x00);
    ILI9341_wr_data(0xAA);
    ILI9341_wr_data(0XB0);
    ILI9341_wr_cmd(ILI9341_PUMP_RATIO_CONTROL);								// ???
    ILI9341_wr_data(0x30);
    ILI9341_wr_cmd(ILI9341_POWER_CONTROL_1);								// jakies napiecie GVDD
    ILI9341_wr_data(0x25);
    ILI9341_wr_cmd(ILI9341_POWER_CONTROL_2);								// wspolczynnik step-up
    ILI9341_wr_data(0x11);
    ILI9341_wr_cmd(ILI9341_VCOM_CONTROL_1);									// jakies napiecia VCOMH i VCOML
    ILI9341_wr_data(0x5C);
    ILI9341_wr_data(0x4C);
    ILI9341_wr_cmd(ILI9341_VCOM_CONTROL_2);									// jakies stosunki VCOMH/VCOML
    ILI9341_wr_data(0x94);
    ILI9341_wr_cmd(ILI9341_DRIVER_TIMING_CONTROL_A);						// ??? bez tego nie dziala
    ILI9341_wr_data(0x85);
    ILI9341_wr_data(0x01);
    ILI9341_wr_data(0x78);
    ILI9341_wr_cmd(ILI9341_DRIVER_TIMING_CONTROL_B);						// ???
    ILI9341_wr_data(0x00);
    ILI9341_wr_data(0x00);
    ILI9341_wr_cmd(ILI9341_COLMOD_PIXEL_FORMAT_SET);						// ok
    ILI9341_wr_data(0x55);
    ILI9341_wr_cmd(ILI9341_FRAME_RATE_CONTROL_NORMAL);						// stabilniejszy obraz bez migotania
    ILI9341_wr_data(0x00);
    ILI9341_wr_data(0x10);
    ILI9341_wr_cmd(ILI9341_SLEEP_OUT);										// ok
    ILI9341_wr_cmd(ILI9341_DISPLAY_ON);										// ok
}

/* Read raw data from RAM in LCD */
/*
uint16_t ILI9341_rd_ram()
{
    uint16_t data = ILI9341_rd_reg(ILI9341_RW_GRAM);
    uint16_t output = data >> 11;											// B
    output |= data & 0b0000011111100000;									// G
    output |= data << 11;													// R
    return output;
}
*/

/* Set display rotation
 * 0 - up
 * 1 - right
 * 2 - down
 * 3 - left
 * */

void ILI9341_set_rotation(uint8_t orientation)
{
    rotation = orientation;

    switch (orientation)
    {
        case PORTRAIT:														// up
            lcd_width = TFT_HEIGHT;
            lcd_height = TFT_WIDTH;
            ILI9341_wr_cmd(ILI9341_MEMORY_ACCESS_CONTROL);
            ILI9341_wr_data(0x40 | 0x08);
            break;

        case LANDSCAPE:														// right
            lcd_width = TFT_WIDTH;
            lcd_height = TFT_HEIGHT;
            ILI9341_wr_cmd(ILI9341_MEMORY_ACCESS_CONTROL);
            ILI9341_wr_data(0x20 | 0x08);
            break;

        case PORTRAIT_REV:													// down
            lcd_width = TFT_HEIGHT;
            lcd_height = TFT_WIDTH;
            ILI9341_wr_cmd(ILI9341_MEMORY_ACCESS_CONTROL);
            ILI9341_wr_data(0x80 | 0x08);
            break;

        case LANDSCAPE_REV:													//  left
            lcd_width = TFT_WIDTH;
            lcd_height = TFT_HEIGHT;
            ILI9341_wr_cmd(ILI9341_MEMORY_ACCESS_CONTROL);
            ILI9341_wr_data(0x40 | 0x80 | 0x20 | 0x08);
            break;
    }
}

/* Set current drawing coordinates */
void ILI9341_set_address(uint16_t x, uint16_t y)
{
    if ((x > lcd_width) || (y > lcd_height)) return;						// Nothing if out of the screen

    ILI9341_wr_cmd(ILI9341_COLUMN_ADDRESS_SET);
    ILI9341_wr_data(x >> 8);
    ILI9341_wr_data(x);
    ILI9341_wr_data(lcd_width >> 8);
    ILI9341_wr_data(lcd_width);
    ILI9341_wr_cmd(ILI9341_PAGE_ADDRESS_SET);
    ILI9341_wr_data(y >> 8);
    ILI9341_wr_data(y);
    ILI9341_wr_data(lcd_height >> 8);
    ILI9341_wr_data(lcd_height);
    ILI9341_wr_cmd(ILI9341_MEMORY_WRITE);
}

/* Set current drawing window */
void ILI9341_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    if ((x0 > lcd_width) || (y0 > lcd_height) || (x1 > lcd_width) || (y1 > lcd_height)) return;						// Nothing if out of the screen

    ILI9341_wr_cmd(ILI9341_COLUMN_ADDRESS_SET);
    ILI9341_wr_data(x0 >> 8);
    ILI9341_wr_data(x0);
    ILI9341_wr_data(x1 >> 8);
    ILI9341_wr_data(x1);
    ILI9341_wr_cmd(ILI9341_PAGE_ADDRESS_SET);
    ILI9341_wr_data(y0 >> 8);
    ILI9341_wr_data(y0);
    ILI9341_wr_data(y1 >> 8);
    ILI9341_wr_data(y1);
    ILI9341_wr_cmd(ILI9341_MEMORY_WRITE);
}

void ILI9341_draw_pixel(uint16_t x, uint16_t y, uint16_t color)
{
    ILI9341_set_address(x, y);
    ILI9341_push_color(color);
}

static inline void ILI9341_push_color(uint16_t color)
{
    ILI9341_wr_data(color >> 8);
    ILI9341_wr_data(color);
}
/* 8 colors on display */
/*
void ILI9341_set_8colors()
{
    ILI9341_wr_reg(ILI9341_DISP_CTRL1, 0x013B);
}
*/

/* 64k colors on display */
/*
void ILI9341_set_64kcolors()
{
    ILI9341_wr_reg(ILI9341_DISP_CTRL1, 0x0133);
}
*/

/* Convert RGB to 8bit */
/*
uint8_t rgb_color8(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t color8 = ((r * 7 / 255) << 5) + ((g * 7 / 255) << 2) + (b * 3 / 255);
    return color8;
}
*/

/* Convert RGB to 16bit */
/*
uint16_t rgb_color565(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t color;
    color = r >> 3;															// 00000000_000rrrrr
    color <<= 6;															// 00000rrr_rr000000
    color |= g >> 2;														// 00000rrr_rrgggggg
    color <<= 5;															// rrrrrggg_ggg00000
    color |= b >> 3;														// rrrrrggg_gggbbbbb
    return color;
}
*/

/* Draw character at given coordinates and color */
void ILI9341_chr(uint16_t x, uint16_t y, char c)
{
    if (current_font.x_size == 5)
    {
        ILI9341_set_window(x, y, x + current_font.x_size, y + current_font.y_size);

        for (uint8_t cols = 0; cols < 5; cols++ )								// 5 columns
        {
            uint8_t line = pgm_read_byte(current_font.font + ( (c - ' ') * 5) + cols);		// Characters start with code 32 (space)

            for (uint8_t rows = 0; rows < 8; rows++)							// 8 rows
            {
                if (line & 0x1)													// If bit in pattern set
                {
                    ILI9341_draw_pixel(x + cols, y + rows, current_font.fg_color);
                }
                else
                {
                    if (current_font.bg_color != TRANSPARENT)
                    {
                        ILI9341_draw_pixel(x + cols, y + rows, current_font.bg_color);
                    }
                }

                line >>= 1;														// Next bit in pattern
            }
        }
    }
    else
    {
        const uint8_t *adr = current_font.font + ((c - ' ') * ((current_font.x_size + 7) / 8) * current_font.y_size);

        if (current_font.bg_color != TRANSPARENT) ILI9341_draw_mono_bmp(x, y, current_font.x_size, current_font.y_size, adr, current_font.fg_color, current_font.bg_color);
        else ILI9341_draw_mono_trans_bmp(x, y, current_font.x_size, current_font.y_size, adr, current_font.fg_color);
    }
}

/* Draw text at given coordinates */
void ILI9341_txt(uint16_t x, uint16_t y, char *string)
{
    while (*string)
    {
        ILI9341_chr(x, y, *string);

        if (current_font.x_size == 5) x += 6;
        else x += current_font.x_size;

        string++;
    }
}

/* Set parameters for current text */
void ILI9341_set_font(font_t font)
{
    current_font = font;
}

/* Set current draw color */
void ILI9341_set_draw_color(uint16_t color)
{
    draw_color = color;
}

/* Fill screen with color */
void ILI9341_cls(uint16_t color)
{
    ILI9341_set_window(0, 0, lcd_width - 1, lcd_height - 1);
    uint32_t i = 76800;									// 320x240=76800

    while (i--)
    {
        ILI9341_wr_data(color >> 8);
        ILI9341_wr_data(color);
    }
}

/* Draw line on the display */
void ILI9341_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t d, dx, dy, ai, bi;												// aux variables
    int8_t xi, yi;
    int16_t ax = x0, ay = y0;

    if (x0 < x1)															// drawing direction
    {
        xi = 1;
        dx = x1 - x0;
    }
    else
    {
        xi = -1;
        dx = x0 - x1;
    }

    if (y0 < y1)															// drawing direction
    {
        yi = 1;
        dy = y1 - y0;
    }
    else
    {
        yi = -1;
        dy = y0 - y1;
    }

    ILI9341_draw_pixel(ax, ay, color);							// First pixel

    if (dx > dy)															// Leading axis X
    {
        ai = (dy - dx) * 2;
        bi = dy * 2;
        d = bi - dx;

        while (ax != x1)													// Loop x
        {
            if (d >= 0)														// Test coefficient
            {
                ax += xi;
                ay += yi;
                d += ai;
            }
            else
            {
                d += bi;
                ax += xi;
            }

            ILI9341_draw_pixel(ax, ay, color);
        }
    }
    else																	// Leading axle Y
    {
        ai = ( dx - dy ) * 2;
        bi = dx * 2;
        d = bi - dy;

        while (ay != y1)													// Loop y
        {
            if (d >= 0)														// Test coefficient
            {
                ax += xi;
                ay += yi;
                d += ai;
            }
            else
            {
                d += bi;
                ay += yi;
            }

            ILI9341_draw_pixel(ax, ay, color);
        }
    }
}

/* Draw fast line
 * - HORIZONTAL
 * | VERTICAL
 * / UP_SLOPE
 * \ DN_SLOPE */
/*
void ILI9341_draw_fast_line(uint16_t x, uint16_t y, uint16_t lenght, uint16_t color, enum direction_t line_direction)
{
    if ((rotation == LANDSCAPE ) || (rotation == LANDSCAPE_REV))			// Landscape
    {
        ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, y);								// Set beginning of line
        ILI9341_wr_reg(ILI9341_GRAM_VER_AD, x);
    }
    else																	// Portrait
    {
        ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, x);								// Set beginning of line
        ILI9341_wr_reg(ILI9341_GRAM_VER_AD, y);
    }

    for (uint16_t i = 0; i < lenght; i++)
    {
        switch (line_direction)
        {
            case HORIZONTAL:
                break;

            case VERTICAL:
                if ((rotation == 0) || (rotation == 2))	ILI9341_wr_reg(ILI9341_GRAM_VER_AD, y + i);
                else ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, y + i);

                break;

            case UP_SLOPE:
                if ((rotation == PORTRAIT) || (rotation == PORTRAIT_REV))
                {
                    ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, x + i);
                    ILI9341_wr_reg(ILI9341_GRAM_VER_AD, y - i);
                }
                else
                {
                    ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, y - i);
                    ILI9341_wr_reg(ILI9341_GRAM_VER_AD, x + i);
                }

                break;

            case DN_SLOPE:
                if ((rotation == PORTRAIT) || (rotation == PORTRAIT_REV))
                {
                    ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, x + i);
                    ILI9341_wr_reg(ILI9341_GRAM_VER_AD, y + i);
                }
                else
                {
                    ILI9341_wr_reg(ILI9341_GRAM_HOR_AD, y + i);
                    ILI9341_wr_reg(ILI9341_GRAM_VER_AD, x + i);
                }

                break;
        }

        ILI9341_wr_reg(ILI9341_RW_GRAM, color);								// Point on line
    }
}
*/

/* Draw polygon on the display
 * nodes[]: table of nodes
 * count: number of lines
 * color: color
 * close: 0 - don't close, 1 - close polygon */
void ILI9341_draw_polygon(uint16_t nodes[], uint8_t count, uint16_t color, uint8_t close)
{
    uint8_t node_id = 0;
    uint16_t x0, y0, x1 = 0, y1 = 0;										// Only to avoid warning

    while ((node_id / 2) < count)
    {
        x0 = nodes[node_id];
        y0 = nodes[node_id + 1];
        node_id += 2;
        x1 = nodes[node_id];
        y1 = nodes[node_id + 1];
        ILI9341_draw_line(x0, y0, x1, y1, color);
    }

    if (close) ILI9341_draw_line(x1, y1, nodes[0], nodes[1], color);		// Close polygon
}

/* Draw a circle with given center, radius, fill flag and color */
void ILI9341_draw_circle(uint16_t x, uint16_t y, uint8_t radius, bool fill, uint16_t color)
{
    uint8_t repeat = radius;

    do
    {
        int16_t t = 0;
        int16_t err = 0;

        while (radius >= t)
        {
            ILI9341_draw_pixel(x + radius, y + t, color);
            ILI9341_draw_pixel(x + t, y + radius, color);
            ILI9341_draw_pixel(x - t, y + radius, color);
            ILI9341_draw_pixel(x - radius, y + t, color);
            ILI9341_draw_pixel(x - radius, y - t, color);
            ILI9341_draw_pixel(x - t, y - radius, color);
            ILI9341_draw_pixel(x + t, y - radius, color);
            ILI9341_draw_pixel(x + radius, y - t, color);
            t += 1;
            err += 1 + 2 * t;

            if (2 * (err - radius) + 1 > 0)
            {
                radius -= 1;
                err += 1 - 2 * radius;
            }
        }

        repeat--;
        radius = repeat;
    }
    while ((radius > 0) && fill);
}

/* Draw triangle with given nodes and colors*/
void ILI9341_draw_triangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t triangle[3][2] =
    {
        {x0, y0},
        {x1, y1},
        {x2, y2}
    };
    ILI9341_draw_polygon(*triangle, 2, color, 1);
}

/* Draw rectangle with given nodes and colors*/
void ILI9341_draw_rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint16_t rectangle[4][2] =
    {
        {x0, y0},
        {x1, y0},
        {x1, y1},
        {x0, y1}
    };
    ILI9341_draw_polygon(*rectangle, 3, color, 1);
}

/* Draw 1-bit bitmap with transparent background */
void ILI9341_draw_mono_trans_bmp(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *bitmap, uint16_t color)
{
    uint16_t byte_width = (width + 7) / 8;
    uint8_t pattern = pgm_read_byte(bitmap);

    for (uint16_t rows = 0; rows < height; rows++)							// For every row in bitmap pattern
    {
        for (uint16_t cols = 0; cols < width; cols++)						// For every column in bitmap pattern
        {
            if (pattern & 0x80) ILI9341_draw_pixel(x + cols, y + rows, color);	// If bit in pattern is set, pixel in foreground color

            if (cols & 7) pattern <<= 1;									// Eight bits to draw
            else pattern = pgm_read_byte(bitmap + rows * byte_width + cols / 8); // Next byte of pattern
        }
    }
}

/* Draw 1-bit bitmap with given foreground and background color */
void ILI9341_draw_mono_bmp(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *bitmap, uint16_t fg, uint16_t bg)
{
    ILI9341_set_window(x, y, x + width, y + height);
    uint16_t byte_width = (width + 7) / 8;
    uint8_t pattern = pgm_read_byte(bitmap);

    for (uint16_t rows = 0; rows < height; rows++)							// For every row in bitmap pattern
    {
        for (uint16_t cols = 0; cols < width + 1; cols++)					// For every column in bitmap pattern
        {
            if (pattern & 0x80) ILI9341_push_color(fg);						// If bit in pattern is set, pixel in foreground color
            else
                ILI9341_push_color(bg);

            if (cols & 7) pattern <<= 1;									// Eight bits to draw
            else pattern = pgm_read_byte(bitmap + rows * byte_width + cols / 8); // Next byte of pattern
        }
    }
}

/* Draw 16-bit color bitmap
 * (overlaps if on the window edge) */
void ILI9341_draw_color_bmp(uint16_t x, uint16_t y, uint16_t height, uint16_t width, const uint16_t *bitmap)
{
    ILI9341_set_window(x, y, x + width - 1, y + height - 1);

    for (uint16_t rows = 0; rows < height; rows++)
    {
        for (uint16_t cols = 0; cols < width; cols++)
        {
            ILI9341_push_color(pgm_read_word(bitmap + (width * rows) + cols));
        }
    }
}

/* Reverse all colors on the display */
/*
void ILI9341_negative()
{
    ILI9341_wr_reg(ILI9341_GATE_SCAN_CTRL2, ILI9341_rd_reg(ILI9341_GATE_SCAN_CTRL2) ^ 1);
}
*/

/* Hardware roll screen vertical (portrait) or horizontal (landscape) */
/*
void ILI9341_scroll(uint16_t shift)
{
    ILI9341_wr_reg(ILI9341_GATE_SCAN_CTRL3, shift);
}
*/