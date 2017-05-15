﻿/*
 * bmp_color.h
 *
 *  Author: kostuch@skeletondevices.com
 */

#ifndef BMP_COLOR_H_
#define BMP_COLOR_H_

// width=32   height=32
// Size in pixel is important when display pic!

const uint16_t PROGMEM suzuki[]  = {
	0x3FE3, 0x47E5, 0x3FE6, 0x47E7, 0x5789, 0x6F0C, 0x8650, 0x0080,
	0x0020, 0x0000, 0x0000, 0x0000, 0x0001, 0x0801, 0x0800, 0x0800,
	0x0000, 0x0800, 0x0000, 0x0820, 0x0021, 0x0001, 0x0000, 0x0800,
	0x0000, 0x0000, 0x0000, 0x0840, 0x7BE0, 0xF789, 0xF768, 0xF727,
	0x4FE6, 0x47E6, 0x4FC9, 0x5F6B, 0x772D, 0x0140, 0x00E0, 0x0060,
	0x0020, 0x0020, 0x0821, 0x0000, 0x0001, 0x0800, 0x2000, 0x2000,
	0x3820, 0x2000, 0x1800, 0x0800, 0x0001, 0x0021, 0x0820, 0x0000,
	0x0820, 0x0000, 0x1060, 0x52A0, 0xD688, 0xF7A9, 0xFFAB, 0xEF09,
	0x47E6, 0x57A9, 0x6ECC, 0x0100, 0x0080, 0x0060, 0x0040, 0x0040,
	0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x4000, 0x8882,
	0xA8E3, 0x8041, 0x3000, 0x1000, 0x0800, 0x0000, 0x0000, 0x0800,
	0x0800, 0x1880, 0x7BC2, 0xE72B, 0xF7A9, 0xF7AA, 0xE6EC, 0x8BE2,
	0x57A9, 0x674C, 0x0100, 0x0040, 0x0020, 0x0821, 0x0000, 0x0000,
	0x0020, 0x0000, 0x0820, 0x0800, 0x1800, 0x4000, 0x98A2, 0xC8C2,
	0xD882, 0xD0A3, 0x90A4, 0x4800, 0x2800, 0x1000, 0x0800, 0x0800,
	0x20C0, 0x9466, 0xF78C, 0xFFCA, 0xF7AA, 0xBDE7, 0x5280, 0x1880,
	0x6F0C, 0x0140, 0x0060, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0800, 0x2000, 0x6000, 0xA862, 0xD061, 0xE881,
	0xE841, 0xF062, 0xD862, 0xB883, 0x6000, 0x2800, 0x1800, 0x2900,
	0xBD89, 0xFF8C, 0xFFE9, 0xFFCA, 0xCE4A, 0x3A00, 0x0020, 0x0020,
	0x8E91, 0x00C0, 0x0040, 0x0800, 0x0020, 0x0000, 0x1021, 0x0800,
	0x0800, 0x1800, 0x3000, 0x6800, 0xC0C4, 0xE062, 0xF041, 0xF820,
	0xF800, 0xF800, 0xF821, 0xE882, 0xC0C3, 0x7840, 0x4000, 0xA3E8,
	0xFF8E, 0xFFAA, 0xFFEB, 0xCE68, 0x4A40, 0x0840, 0x0020, 0x0021,
	0x0040, 0x0040, 0x0020, 0x0020, 0x0000, 0x0000, 0x0000, 0x1000,
	0x1800, 0x4000, 0x9040, 0xD0C3, 0xE042, 0xF022, 0xF820, 0xF800,
	0xF800, 0xF821, 0xF000, 0xF040, 0xE840, 0xD8C2, 0xA8E0, 0xBB04,
	0xFECC, 0xF74C, 0xC5EA, 0x4220, 0x0840, 0x0020, 0x0000, 0x0001,
	0x0801, 0x0000, 0x0020, 0x0020, 0x0800, 0x1000, 0x2000, 0x3000,
	0x6841, 0xA0C2, 0xD8A3, 0xE841, 0xF042, 0xF041, 0xF041, 0xF820,
	0xF821, 0xF800, 0xF820, 0xF820, 0xF820, 0xF040, 0xD8A0, 0xC180,
	0xB2C0, 0xA382, 0x4960, 0x0800, 0x0820, 0x0000, 0x0001, 0x0801,
	0x0000, 0x0041, 0x0000, 0x0800, 0x1000, 0x2800, 0x5800, 0xA8A3,
	0xD0A2, 0xE061, 0xE821, 0xF062, 0xD041, 0xC821, 0xD881, 0xE861,
	0xF020, 0xF800, 0xF800, 0xF840, 0xF820, 0xF820, 0xF020, 0xE081,
	0xC8C0, 0x98A0, 0x3800, 0x1800, 0x0800, 0x0020, 0x0020, 0x0000,
	0x0020, 0x0000, 0x1801, 0x2800, 0x4800, 0x8061, 0xC0E4, 0xD882,
	0xF021, 0xF800, 0xF821, 0xF021, 0xD041, 0x9800, 0xA800, 0xC860,
	0xE080, 0xF080, 0xF841, 0xF820, 0xF820, 0xF800, 0xF842, 0xF801,
	0xF062, 0xD082, 0xA0E4, 0x4800, 0x2800, 0x0800, 0x0800, 0x0800,
	0x0040, 0x1000, 0x4000, 0x8883, 0xB8A2, 0xD8A3, 0xE061, 0xF020,
	0xF800, 0xF820, 0xF800, 0xF821, 0xF041, 0xD841, 0x9800, 0x8000,
	0xA8C0, 0xE1E3, 0xD8C0, 0xE860, 0xF001, 0xF822, 0xF800, 0xF800,
	0xF000, 0xF061, 0xD061, 0xB0C3, 0x5800, 0x2800, 0x1000, 0x1001,
	0x0020, 0x1000, 0x5862, 0xA125, 0xD0C4, 0xE841, 0xF821, 0xF820,
	0xF820, 0xF800, 0xF820, 0xF800, 0xF821, 0xE841, 0xD0A3, 0xB0C1,
	0xB181, 0xFBC8, 0xFBA8, 0xE1A1, 0xF081, 0xF801, 0xF820, 0xF820,
	0xF841, 0xF020, 0xF082, 0xC082, 0x9965, 0x3841, 0x1800, 0x0800,
	0x0000, 0x0800, 0x1800, 0x5021, 0x98A3, 0xD0A4, 0xE021, 0xF841,
	0xF800, 0xF800, 0xF800, 0xF800, 0xF820, 0xF821, 0xE821, 0xD8C1,
	0xDA02, 0xFC67, 0xFE0B, 0xFD4A, 0xE181, 0xE860, 0xF000, 0xF820,
	0xF020, 0xE861, 0xD061, 0xB925, 0x60C3, 0x1800, 0x0800, 0x0000,
	0x0801, 0x0800, 0x1000, 0x1800, 0x4800, 0x8842, 0xC8C3, 0xE062,
	0xF021, 0xF801, 0xF800, 0xF820, 0xF800, 0xF821, 0xF821, 0xE840,
	0xD8E0, 0xF303, 0xFD89, 0xF4A7, 0xD1E2, 0xC8C1, 0xD8C2, 0xD0A1,
	0xD0C3, 0xB8C3, 0xA082, 0x5800, 0x3000, 0x1000, 0x0000, 0x0020,
	0x0000, 0x0800, 0x0000, 0x0820, 0x1000, 0x3000, 0x6020, 0xA8C3,
	0xD882, 0xF041, 0xF020, 0xF840, 0xF800, 0xF800, 0xF800, 0xF800,
	0xF040, 0xE8A0, 0xF1E2, 0xD1E2, 0x7800, 0x6000, 0x6020, 0x5820,
	0x3800, 0x3000, 0x2000, 0x1800, 0x1000, 0x0800, 0x0020, 0x0040,
	0x0800, 0x0800, 0x0020, 0x0040, 0x0020, 0x0800, 0x2000, 0x4800,
	0xA042, 0xD0C3, 0xD881, 0xE860, 0xF860, 0xF840, 0xF820, 0xF800,
	0xF801, 0xF820, 0xF040, 0xD8A1, 0xB0C3, 0x7000, 0x4000, 0x2000,
	0x1800, 0x0821, 0x0800, 0x0000, 0x0801, 0x0800, 0x0020, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0020, 0x0000, 0x0800, 0x0800, 0x1800,
	0x2800, 0x7062, 0xB0E2, 0xD8E1, 0xE0C0, 0xF080, 0xF020, 0xF800,
	0xF820, 0xF800, 0xF020, 0xF041, 0xE061, 0xD082, 0x9000, 0x5000,
	0x1800, 0x0800, 0x0000, 0x0000, 0x0000, 0x0800, 0x0000, 0x0001,
	0x0800, 0x0000, 0x0020, 0x0021, 0x0820, 0x0800, 0x1800, 0x1800,
	0x2800, 0x3800, 0x7800, 0xDA24, 0xFB46, 0xE1A0, 0xF0C0, 0xF040,
	0xF800, 0xF800, 0xF841, 0xF820, 0xF800, 0xF041, 0xD8C3, 0xA0A3,
	0x5800, 0x2000, 0x1800, 0x0800, 0x0820, 0x0000, 0x0801, 0x0001,
	0x0000, 0x0800, 0x0000, 0x0800, 0x1000, 0x2800, 0x4000, 0x6000,
	0x7820, 0x8000, 0x98C0, 0xF3C8, 0xFD8A, 0xFD49, 0xF2A2, 0xE0C0,
	0xF040, 0xF841, 0xF000, 0xF800, 0xF820, 0xF000, 0xE040, 0xD8A2,
	0xC0A3, 0x8021, 0x2800, 0x1000, 0x0000, 0x0000, 0x0021, 0x0001,
	0x0800, 0x0800, 0x1800, 0x2000, 0x5001, 0x8082, 0xB0C4, 0xC0C3,
	0xC8C3, 0xC8C2, 0xC922, 0xD243, 0xFCE8, 0xFDEB, 0xFCAA, 0xE1C2,
	0xE081, 0xF041, 0xF841, 0xF841, 0xF841, 0xF820, 0xF841, 0xE820,
	0xE842, 0xC8A3, 0x88A3, 0x3800, 0x2000, 0x0800, 0x0801, 0x0001,
	0x0000, 0x1800, 0x3800, 0x8883, 0xC0E3, 0xD861, 0xE061, 0xF061,
	0xF060, 0xE840, 0xE840, 0xE080, 0xE160, 0xFAC5, 0xC1A2, 0x8800,
	0xB0A1, 0xD0A2, 0xE861, 0xF820, 0xF800, 0xF821, 0xF000, 0xF842,
	0xF841, 0xE841, 0xD061, 0xB0E3, 0x4800, 0x1800, 0x0800, 0x0800,
	0x0820, 0x1000, 0x6905, 0xA945, 0xD082, 0xF041, 0xF841, 0xF800,
	0xF800, 0xF820, 0xF821, 0xF000, 0xF881, 0xD880, 0xC102, 0x9000,
	0x8000, 0x9800, 0xD082, 0xE861, 0xF821, 0xF820, 0xF801, 0xF801,
	0xF801, 0xF041, 0xE062, 0xC104, 0x7945, 0x1800, 0x1000, 0x0800,
	0x0000, 0x1020, 0x1800, 0x6081, 0xB0C3, 0xD882, 0xE820, 0xF820,
	0xF820, 0xF820, 0xF800, 0xF841, 0xF000, 0xF041, 0xE060, 0xD8A2,
	0xB040, 0x8000, 0x7800, 0xB882, 0xE841, 0xF800, 0xF820, 0xF820,
	0xE820, 0xE0C3, 0xA8C3, 0x7062, 0x2800, 0x0800, 0x0000, 0x0000,
	0x5AC8, 0x1880, 0x1000, 0x2000, 0x5800, 0xA080, 0xD0E0, 0xE080,
	0xF040, 0xF800, 0xF841, 0xF820, 0xF801, 0xF821, 0xF821, 0xE841,
	0xE082, 0xC062, 0x8800, 0x9800, 0xE841, 0xF841, 0xF040, 0xE081,
	0xC8C2, 0x9020, 0x5000, 0x2800, 0x1000, 0x0000, 0x0060, 0x0020,
	0xFFFA, 0x7369, 0x0840, 0x0800, 0x1800, 0x50A0, 0x9A00, 0xC9E0,
	0xD880, 0xF021, 0xF020, 0xF820, 0xF800, 0xF800, 0xF800, 0xF820,
	0xF021, 0xE841, 0xD861, 0xE061, 0xF021, 0xF042, 0xD062, 0xB0C4,
	0x5800, 0x3000, 0x2000, 0x1000, 0x0000, 0x0040, 0x0060, 0x0060,
	0xFFF8, 0xB56E, 0x18A0, 0x1080, 0x5AC2, 0xBD8A, 0xFE8C, 0xF529,
	0xC9A3, 0xD0A2, 0xE861, 0xF041, 0xF820, 0xF820, 0xF800, 0xF821,
	0xF800, 0xF820, 0xF840, 0xF061, 0xE862, 0xD0A3, 0xA063, 0x5000,
	0x2000, 0x0800, 0x1001, 0x0001, 0x0841, 0x0040, 0x00C0, 0x9690,
	0xFFF5, 0xF752, 0x7321, 0xACE6, 0xE6EB, 0xFF8C, 0xFFAB, 0xFF2E,
	0x9AE5, 0x7860, 0xB8C3, 0xE082, 0xF020, 0xF820, 0xF000, 0xF800,
	0xF800, 0xF800, 0xF040, 0xE060, 0xB8C3, 0x7821, 0x3000, 0x1800,
	0x0800, 0x0800, 0x0820, 0x0000, 0x0000, 0x0060, 0x0160, 0x6F0C,
	0xFFF8, 0xF772, 0xF72D, 0xFF8B, 0xFFEB, 0xFFA9, 0xEF2B, 0xA4E7,
	0x28C0, 0x2000, 0x6800, 0xA881, 0xD8A2, 0xE861, 0xF841, 0xF841,
	0xF821, 0xF021, 0xE081, 0xB8C2, 0x6000, 0x2800, 0x1801, 0x0000,
	0x0820, 0x0800, 0x0000, 0x0000, 0x0061, 0x00A0, 0x6F2D, 0x4F89,
	0xFFFD, 0xFFF9, 0xFFAD, 0xFFC9, 0xFF88, 0xF74B, 0x7BA3, 0x18A0,
	0x0000, 0x0800, 0x1800, 0x3800, 0x7840, 0xB8E3, 0xE041, 0xF021,
	0xE820, 0xD882, 0xA0A2, 0x5000, 0x2000, 0x1000, 0x0000, 0x0002,
	0x0000, 0x0820, 0x0000, 0x0020, 0x0060, 0x0120, 0x5729, 0x4FE8,
	0xFFFF, 0xFFFB, 0xFFB1, 0xFFAC, 0xFFCC, 0xB545, 0x18A0, 0x0020,
	0x0020, 0x0020, 0x0020, 0x0800, 0x2800, 0x5800, 0xB0A3, 0xC8C3,
	0xD0E4, 0x9841, 0x5000, 0x2000, 0x0800, 0x0000, 0x0001, 0x0001,
	0x0840, 0x0040, 0x00A0, 0x00A0, 0x0120, 0x6EED, 0x57A9, 0x47E6,
	0xFFFF, 0xFFFE, 0xFFFB, 0xFFF9, 0xF771, 0xEF10, 0xA4EB, 0x62E6,
	0x20C0, 0x0820, 0x0000, 0x0020, 0x0800, 0x2000, 0x3000, 0x6082,
	0x68C3, 0x3800, 0x1800, 0x0800, 0x0000, 0x0000, 0x0020, 0x0020,
	0x0040, 0x00C0, 0x0120, 0x6F2C, 0x5F4A, 0x57A8, 0x47E6, 0x47E6,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFD, 0xFFF9, 0xFFF6, 0xFFF8, 0xFFF9,
	0x838A, 0x18A0, 0x0020, 0x0001, 0x0821, 0x0800, 0x1000, 0x1000,
	0x2000, 0x1800, 0x0800, 0x0000, 0x0821, 0x0020, 0x0020, 0x0040,
	0x0080, 0x8E90, 0x6F0C, 0x5788, 0x4FE7, 0x47E6, 0x47E6, 0x3FE6
};

const uint16_t PROGMEM test_rgyb[] = {
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800,
  0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F, 0x481F,
  0x07E5, 0x07E4, 0x07E4, 0x07E4, 0x07E5, 0x07E4, 0x07E4, 0x07E4,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800, 0xF800
};

#endif /* BMP_COLOR_H_ */