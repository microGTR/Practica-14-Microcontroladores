#ifndef MAX7219_H
#define MAX7219_H

#include "pico/stdlib.h"

void max7219_init(uint clk_pin, uint din_pin, uint cs_pin);
void max7219_display(uint clk_pin, uint din_pin, uint cs_pin, uint8_t *buffer);
void max7219_brightness(uint clk_pin, uint din_pin, uint cs_pin, uint8_t brightness);

#endif