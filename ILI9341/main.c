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
//#include "controls.h"

// PETIT
#include "diskio.h"
#include "pff.h"
#include "xitoa.h"
#include "suart.h"
#include "sd_card.h"


/*---------------------------------------------------------*/
/* Work Area                                               */
/*---------------------------------------------------------*/

char Line[64];		/* Console input buffer */

static void put_rc (FRESULT rc)
{
	const char *p;
	static const char PROGMEM str[]  =
	    "OK\0" "DISK_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
	    "NOT_OPENED\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0";
	FRESULT i;

	for (p = str, i = 0; i != rc && pgm_read_byte_near(p); i++)
	{
		while (pgm_read_byte_near(p++));
	}

	xprintf(PSTR("rc=%u FR_%S\n"), (WORD)rc, p);
}

static void put_drc (BYTE res)
{
	xprintf(PSTR("rc=%d\n"), res);
}

static int get_line (char *buff, int len)
{
	BYTE c;
	int i;
	i = 0;

	for (;;)
	{
		c = rcvr();

		if (c == '\r') break;

		if ((c == '\b') && i) i--;

		if ((c >= ' ') && (i < len - 1))
			buff[i++] = c;
	}

	buff[i] = 0;
	xmit('\n');
	return i;
}

static void put_dump (const BYTE *buff, DWORD ofs, int cnt)
{
	BYTE n;
	xitoa(ofs, 16, -8); xputc(' ');

	for (n = 0; n < cnt; n++)
	{
		xputc(' ');	xitoa(buff[n], 16, -2);
	}

	xputs(PSTR("  "));

	for (n = 0; n < cnt; n++)
		xputc(((buff[n] < 0x20) || (buff[n] >= 0x7F)) ? '.' : buff[n]);

	xputc('\n');
}

void touch_calibration(void);
void load_picture(const char *file_name, uint16_t x, uint16_t y);
void save_picture(const char *file_name, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

char driver_id_a[16];

int main(void)
{
	
	ILI9341_init();															// Inicjalizacja LCD
	XPT2046_init_io();														// Inicjalizacja digitizera
	SDCARD_init_io();														// Inicjalizacja pinow SD (tylko CS)
	XPT2046_rd_ee_cal();													// Odczyt matrycy kalibracji
	ILI9341_set_rotation(LANDSCAPE);										// Landscape
	//touch_calibration();													// KALIBRACJA dotyku
	ILI9341_cls(BLUE);														// Ekran na niebiesko
	ILI9341_set_font((font_t) {font16x16, 16, 16, YELLOW, BLUE});			// font 16x16
	xfunc_out = xmit;														// Join UART and xitoa module - DEBUG via UART
	
	load_picture("M.BIN", 0, 0);											// Zaladuj obrazek z karty SD
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

	while (1) ;
}

int main_pff (void)
{
	ILI9341_init();															// Inicjalizacja LCD
	XPT2046_init_io();														// Inicjalizacja digitizera
	SDCARD_init_io();														// Inicjalizacja pinow SD (tylko CS)
	ILI9341_set_rotation(LANDSCAPE);										// Landscape
	ILI9341_cls(BLUE);
	char *ptr;
	long p1, p2;
	int n;
	BYTE res;
	UINT s1, s2, s3, ofs, cnt, bw;
	FATFS fs;																// File system object
	DIR dir;																// Directory object
	FILINFO fno;															// File information
	xfunc_out = xmit;														// Join UART and xitoa module
	xputs(PSTR("\nPFF test monitor\n"));

	for (;;)
	{
		xputc('>');
		get_line(Line, sizeof Line);
		ptr = Line;

		switch (*ptr++)
		{
			case 'd' :
				switch (*ptr++)
				{
					case 'i' :												// di - Initialize physical drive
						res = disk_initialize();
						put_drc(res);
						break;

					case 'd' :												// dd <sector> <ofs> - Dump partial secrtor 128 bytes
						if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;

						s2 = p2;
						res = disk_readp((BYTE *)Line, p1, s2, 128);

						if (res) { put_drc(res); break; }

						s3 = s2 + 128;

						for (ptr = Line; s2 < s3; s2 += 16, ptr += 16, ofs += 16)
						{
							s1 = (s3 - s2 >= 16) ? 16 : s3 - s2;
							put_dump((BYTE *)ptr, s2, s1);
						}

						break;
				}

				break;

			case 'f' :
				switch (*ptr++)
				{
					case 'i' :												// fi - Mount the volume
						put_rc(pf_mount(&fs));
						break;

					case 'o' :												// fo <file> - Open a file
						while (*ptr == ' ') ptr++;

						put_rc(pf_open(ptr));
						break;
#if _USE_READ

					case 'd' :												// fd - Read the file 128 bytes and dump it
						p2 = fs.fptr;
						res = pf_read(Line, sizeof Line, &s1);

						if (res != FR_OK) { put_rc(res); break; }

						ptr = Line;

						while (s1)
						{
							s2 = (s1 >= 16) ? 16 : s1;
							s1 -= s2;
							put_dump((BYTE *)ptr, p2, s2);
							ptr += 16; p2 += 16;
						}

						break;

					case 't' :												// ft - Type the file text (direct output)
						do
						{
							res = pf_read(0, 32768, &s1);

							if (res != FR_OK) { put_rc(res); break; }
						}
						while (s1 == 32768);

						break;
#endif
#if _USE_WRITE

					case 'w' :												// fw <len> <val> - Write data to the file
						if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;

						for (s1 = 0; s1 < sizeof Line; Line[s1++] = (BYTE)p2) ;

						p2 = 0;

						while (p1)
						{
							if ((UINT)p1 >= sizeof Line)
							{
								cnt = sizeof Line; p1 -= sizeof Line;
							}
							else
							{
								cnt = (WORD)p1; p1 = 0;
							}

							res = pf_write(Line, cnt, &bw);					// Write data to the file
							p2 += bw;

							if (res != FR_OK) { put_rc(res); break; }

							if (cnt != bw) break;
						}

						res = pf_write(0, 0, &bw);							// Finalize the write process
						put_rc(res);

						if (res == FR_OK)
							xprintf(PSTR("%lu bytes written.\n"), p2);

						break;

					case 'p' :												// fp - Write console input to the file
						xputs(PSTR("Enter text to write. A blank line finalizes the write operation.\n"));

						for (;;)
						{
							n = get_line(Line, sizeof Line);

							if (!n) break;

							pf_write(Line, n, &bw);
							pf_write("\r\n", 2, &bw);
						}

						res = pf_write(0, 0, &bw);							// Finalize the write process
						put_rc(res);
						break;
#endif
#if _USE_LSEEK

					case 'e' :												// fe - Move file pointer of the file
						if (!xatoi(&ptr, &p1)) break;

						res = pf_lseek(p1);
						put_rc(res);

						if (res == FR_OK)
							xprintf(PSTR("fptr = %lu(0x%lX)\n"), fs.fptr, fs.fptr);

						break;
#endif
#if _USE_DIR

					case 'l' :												// fl [<path>] - Directory listing
						while (*ptr == ' ') ptr++;

						res = pf_opendir(&dir, ptr);

						if (res) { put_rc(res); break; }

						s1 = 0;

						for (;;)
						{
							res = pf_readdir(&dir, &fno);

							if (res != FR_OK) { put_rc(res); break; }

							if (!fno.fname[0]) break;

							if (fno.fattrib & AM_DIR)
								xprintf(PSTR("   <DIR>   %s\n"), fno.fname);
							else
								xprintf(PSTR("%9lu  %s\n"), fno.fsize, fno.fname);

							s1++;
						}

						xprintf(PSTR("%u item(s)\n"), s1);
						break;
#endif
				}

				break;
		}
	}
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
		}
		while (labs(x - touch.x_raw) > MAX_CAL_ERROR || labs(y - touch.y_raw) > MAX_CAL_ERROR);

		_delay_ms(500);
		ILI9341_draw_circle(x, y, 5, true, BLACK);							// Remove old calibration circle
	}

	set_cal_matrix(sample_points);											// Create calibration matrix
	//XPT2046_wr_ee_cal();													// Store it in EEPROM
	ILI9341_set_font((font_t) {font16x16, 16, 16, YELLOW, BLACK});
	ILI9341_txt_P(0, 120, PGM_GETSTR(calibration_txt, cal_end_idx));
}

void load_picture(
    const char *file_name,													// Filename on SD card
    uint16_t x,																// X coordinate
    uint16_t y)																// Y coordinate
{
	char buffer[512];
	UINT bytes_read;
	FATFS fs;
	uint8_t sector;

	if (disk_initialize() == FR_OK)
	{
		if (pf_mount(&fs) == FR_OK)
		{
			if (pf_open(file_name) == FR_OK)
			{
				sector = 0;													// First sector
				uint8_t start_pos;											// Data in buffer start position

				do
				{
					bytes_read = 0;											// Bytes read so far
					pf_read(buffer, sizeof(buffer), &bytes_read);			// Read part of the file to buffer (sector 512b)

					if (!(sector))											// If first (zero) sector
					{
						ILI9341_set_window(x, y, buffer[0] + (buffer[1] << 8) - 1, buffer[2] + (buffer[3] << 8) - 1);	// Set picture size
						start_pos = 4;										// Data start at index 4
					}
					else start_pos = 0;										// Data start at index 0

					// Check if it is full sector or part of it
					for (uint16_t pixel = start_pos; pixel < (bytes_read % sizeof(buffer) ? bytes_read % sizeof(buffer) : sizeof(buffer)); pixel += 2)
					{
						ILI9341_push_color(buffer[pixel] + (buffer[pixel + 1] << 8));
					}
					sector++;
				}
				while (!(bytes_read % sizeof(buffer)));						// Repeat read until the end of the file
			}
			else ILI9341_txt_P(0, 0, PSTR("File open error!"));				// No file
		}
		else ILI9341_txt_P(0, 0, PSTR("FS mount error!"));					// No FAT
	}
	else ILI9341_txt_P(0, 0, PSTR("SD init error!"));						// No card
}

void save_picture(
    const char *file_name,													// Filename on SD card
    uint16_t x0,															// X coordinate left-right
    uint16_t y0,															// Y coordinate
    uint16_t x1,															// X coordinate top-bottom
    uint16_t y1)															// Y coordinate
{
	char buffer[512];
	UINT bytes_written;
	FATFS fs;
	uint16_t size_x = x1 - x0;												// X size
	uint16_t size_y = y1 - y0;												// Y size
	uint32_t bytes_to_write = size_x * size_y;
	uint8_t sectors_to_write = (bytes_to_write / sizeof(buffer) + 1);
	//uint16_t reminder_to_write = bytes_to_write % sizeof(buffer);
	ILI9341_set_window(x0, y0, x1, y1);										// Frame to be saved
	if (disk_initialize() == FR_OK)
	{
		if (pf_mount(&fs) == FR_OK)
		{
			if (pf_open(file_name) == FR_OK)
			{
				uint8_t start_pos;											// Data in buffer start position
				do
				{
					bytes_written = 0;										// Bytes written so far
					if (!(sectors_to_write))								// If first (zero) sector
					{
						buffer[0] = size_x & 0xFF;							// Set picture size LSB and MSB
						buffer[1] = size_x >> 8;
						buffer[2] = size_y & 0xFF;
						buffer[3] = size_y >> 8;
						start_pos = 4;										// Data start at index 4
					}
					else start_pos = 0;										// Data start at index 0

					for (uint16_t pixel = start_pos; pixel < (bytes_written % sizeof(buffer) ? bytes_written % sizeof(buffer) : sizeof(buffer)); pixel += 2)
					{
						uint16_t color = ILI9341_rd_ram();
						buffer[pixel] = color & 0xFF;
						buffer[pixel + 1] = color >> 8;
					}

					if (!(pf_write(buffer, sizeof(buffer), &bytes_written))) ILI9341_txt_P(0, 0, PSTR("File write error!"));	// Error writing file
				}
				while ((bytes_written * sectors_to_write) < bytes_to_write);// Repeat read until the end

				pf_write(0, 0, &bytes_written);								// Finalize the write process
			}
			else ILI9341_txt_P(0, 0, PSTR("File open error!"));				// No file
		}
		else ILI9341_txt_P(0, 0, PSTR("FS mount error!"));					// No FAT
	}
	else ILI9341_txt_P(0, 0, PSTR("SD init error!"));						// No card
}