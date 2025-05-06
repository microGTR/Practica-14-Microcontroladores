#include "max7219.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

void max7219_send(uint clk_pin, uint din_pin, uint cs_pin, uint8_t reg, uint8_t data) {
    gpio_put(cs_pin, 0);
    
    for (int i = 7; i >= 0; i--) {
        gpio_put(clk_pin, 0);
        gpio_put(din_pin, (reg >> i) & 1);
        gpio_put(clk_pin, 1);
    }
    
    for (int i = 7; i >= 0; i--) {
        gpio_put(clk_pin, 0);
        gpio_put(din_pin, (data >> i) & 1);
        gpio_put(clk_pin, 1);
    }
    
    gpio_put(cs_pin, 1);
}

void max7219_init(uint clk_pin, uint din_pin, uint cs_pin) {
    gpio_init(clk_pin);
    gpio_init(din_pin);
    gpio_init(cs_pin);
    
    gpio_set_dir(clk_pin, GPIO_OUT);
    gpio_set_dir(din_pin, GPIO_OUT);
    gpio_set_dir(cs_pin, GPIO_OUT);
    
    gpio_put(cs_pin, 1);
    
    // Configuración del MAX7219
    max7219_send(clk_pin, din_pin, cs_pin, 0x09, 0x00); // Decode mode: no decode
    max7219_send(clk_pin, din_pin, cs_pin, 0x0A, 0x01); // Intensity: medium
    max7219_send(clk_pin, din_pin, cs_pin, 0x0B, 0x07); // Scan limit: all digits
    max7219_send(clk_pin, din_pin, cs_pin, 0x0C, 0x01); // Shutdown: normal operation
    max7219_send(clk_pin, din_pin, cs_pin, 0x0F, 0x00); // Display test: off
}

void max7219_display(uint clk_pin, uint din_pin, uint cs_pin, uint8_t *buffer) {
    for (uint8_t i = 0; i < 8; i++) {
        max7219_send(clk_pin, din_pin, cs_pin, i + 1, buffer[i]);
    }
}

void max7219_brightness(uint clk_pin, uint din_pin, uint cs_pin, uint8_t brightness) {
    if (brightness > 15) brightness = 15;
    max7219_send(clk_pin, din_pin, cs_pin, 0x0A, brightness);
}