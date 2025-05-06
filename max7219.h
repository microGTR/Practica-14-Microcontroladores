#ifndef MAX7219_H
#define MAX7219_H

#include "pico/stdlib.h"

// Inicializa el MAX7219 con los pines especificados
void max7219_init(uint clk_pin, uint din_pin, uint cs_pin);

// Envía un patrón de 8 bytes a la matriz LED
void max7219_display(uint clk_pin, uint din_pin, uint cs_pin, uint8_t *buffer);

// Ajusta el brillo de la matriz (0-15)
void max7219_brightness(uint clk_pin, uint din_pin, uint cs_pin, uint8_t brightness);

#endif // MAX7219_H
