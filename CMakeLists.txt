cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(semaforo_matrices_independientes C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(semaforo
    main.c
    max7219.c
)

target_include_directories(semaforo PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(semaforo pico_stdlib)

pico_add_extra_outputs(semaforo)
