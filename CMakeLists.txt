cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(semaforo_doble C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(semaforo_doble
    main.c
    max7219.c
)

target_include_directories(semaforo_doble PRIVATE ${CMAKE_CURRENT_LIST_DIR})

pico_enable_stdio_usb(semaforo_doble 1)
pico_enable_stdio_uart(semaforo_doble 0)

pico_add_extra_outputs(semaforo_doble)

target_link_libraries(semaforo_doble
    pico_stdlib
    hardware_gpio
    hardware_spi
    hardware_timer
)