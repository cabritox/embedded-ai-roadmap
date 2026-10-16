cmake_minimum_required(VERSION 3.10)
project(Simulator_UART C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# Le decimos a CMake dónde buscar los archivos .h
include_directories(include)

# Le decimos qué archivos .c debe compilar juntos
add_executable(sim_uart
    src/ring_buffer.c
    src/uart.c
    src/uart_mock.c
    main.c
)