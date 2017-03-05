/*
 * literals.h
 *
 * Created: 2017-03-03 16:10:55
 *  Author: potocki
 */ 


#ifndef LITERALS_H_
#define LITERALS_H_

const char cal_prompt[] PROGMEM =	{"Dotknij kolko"};
const char cal_bad[] PROGMEM =		{"Blad kalibracji!"};
const char cal_ok[] PROGMEM =		{"Blad kalibracji!"};
const char cal_next[] PROGMEM =		{"Nastepny..."};

enum cal_txt {cal_prompt_idx = 0, cal_bad_idx = 1, cal_ok_idx = 2, cal_next_idx = 3};

// PGM_P <=> const char *
PGM_P const calibration_txt[4] PROGMEM =
{
cal_prompt,
cal_bad,
cal_ok,
cal_next
};

#endif /* LITERALS_H_ */