/*
 * SPI.h
 *
 * Created: 2017-02-21 12:55:30
 *  Author: potocki
 */ 


#ifndef SPI_H_
#define SPI_H_

enum dev_t {TFT, TOUCH, SDCARD};

void SPI_init(void);
void SPI_write(uint8_t tx, enum dev_t device);
uint8_t SPI_rxtx(uint8_t tx, enum dev_t device);

#endif /* SPI_H_ */