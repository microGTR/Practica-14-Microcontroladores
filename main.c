#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "max7219.h"
#include <string.h>

// Definición de pines
#define SEM1_RED 2
#define SEM1_YELLOW 3
#define SEM1_GREEN 4
#define SEM2_RED 5
#define SEM2_YELLOW 6
#define SEM2_GREEN 7
#define BTN_PEATONAL1 8
#define BTN_PEATONAL2 9
#define DIN1 10
#define CS1 11
#define CLK1 12
#define DIN2 13
#define CS2 14
#define CLK2 15

typedef enum { VERDE, AMARILLO, ROJO } semaforo_estado;

// Variables de estado
volatile bool btn1_pressed = false;
volatile bool btn2_pressed = false;
int tiempo_restante = 10;
semaforo_estado estado_actual = VERDE;
bool semaforo1_activo = true;
bool paso_peatonal1 = false;
bool paso_peatonal2 = false;

// Prototipos de funciones
void btn1_isr(uint gpio, uint32_t events);
void btn2_isr(uint gpio, uint32_t events);

// Patrones para la matriz
uint8_t circulo[8] = {
    0b00111100,
    0b01111110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100
};

uint8_t flecha_der[8] = {
    0b00011000,
    0b00011000,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000,
    0b00000000,
    0b00000000
};

uint8_t flecha_izq[8] = {
    0b00011000,
    0b00110000,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000,
    0b00000000,
    0b00000000
};

uint8_t numeros[10][8] = {
    {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C}, // 0
    {0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x3E}, // 1
    {0x3C, 0x42, 0x02, 0x04, 0x18, 0x20, 0x40, 0x7E}, // 2
    {0x3C, 0x42, 0x02, 0x1C, 0x02, 0x02, 0x42, 0x3C}, // 3
    {0x04, 0x0C, 0x14, 0x24, 0x44, 0x7E, 0x04, 0x04}, // 4
    {0x7E, 0x40, 0x40, 0x7C, 0x02, 0x02, 0x42, 0x3C}, // 5
    {0x3C, 0x42, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x3C}, // 6
    {0x7E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10, 0x10}, // 7
    {0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C}, // 8
    {0x3C, 0x42, 0x42, 0x42, 0x3E, 0x02, 0x42, 0x3C}  // 9
};

void init_gpio() {
    // Configurar semáforos vehiculares
    for(int i = 2; i <= 7; i++) {
        gpio_init(i);
        gpio_set_dir(i, GPIO_OUT);
    }
    
    // Configurar botones
    gpio_init(BTN_PEATONAL1);
    gpio_init(BTN_PEATONAL2);
    gpio_set_dir(BTN_PEATONAL1, GPIO_IN);
    gpio_set_dir(BTN_PEATONAL2, GPIO_IN);
    gpio_pull_up(BTN_PEATONAL1);
    gpio_pull_up(BTN_PEATONAL2);
    
    // Configurar interrupciones
    gpio_set_irq_enabled_with_callback(BTN_PEATONAL1, GPIO_IRQ_EDGE_FALL, true, &btn1_isr);
    gpio_set_irq_enabled_with_callback(BTN_PEATONAL2, GPIO_IRQ_EDGE_FALL, true, &btn2_isr);
}

void semaforo_vehicular(semaforo_estado estado, bool semaforo1) {
    // Apagar todos los LEDs
    for(int i = 2; i <= 7; i++) gpio_put(i, 0);
    
    if(semaforo1) {
        switch(estado) {
            case VERDE:
                gpio_put(SEM1_GREEN, 1);
                gpio_put(SEM2_RED, 1);
                break;
            case AMARILLO:
                gpio_put(SEM1_YELLOW, 1);
                gpio_put(SEM2_RED, 1);
                break;
            case ROJO:
                gpio_put(SEM1_RED, 1);
                gpio_put(SEM2_GREEN, 1);
                break;
        }
    } else {
        switch(estado) {
            case VERDE:
                gpio_put(SEM2_GREEN, 1);
                gpio_put(SEM1_RED, 1);
                break;
            case AMARILLO:
                gpio_put(SEM2_YELLOW, 1);
                gpio_put(SEM1_RED, 1);
                break;
            case ROJO:
                gpio_put(SEM2_RED, 1);
                gpio_put(SEM1_GREEN, 1);
                break;
        }
    }
}

void mostrar_matriz(uint8_t *patron, bool matriz1) {
    max7219_display(matriz1 ? CLK1 : CLK2, 
                   matriz1 ? DIN1 : DIN2
::contentReference[oaicite:0]{index=0}
 
