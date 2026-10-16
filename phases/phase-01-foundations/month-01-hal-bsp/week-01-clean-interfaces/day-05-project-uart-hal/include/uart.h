#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// La Vtable (Interfaz abstracta)
typedef struct
{
    bool (*transmit)(void *ctx, const uint8_t *data, size_t length);
    bool (*receive)(void *ctx, uint8_t *out_data);
} uart_ops_t;

// Puntero opaco
typedef struct UARTDevice uart_t;

// Funciones públicas
uart_t *uart_create(const uart_ops_t *ops, void *ctx);
bool uart_send(uart_t *self, const uint8_t *data, size_t length);
bool uart_read(uart_t *self, uint8_t *out_data);

#endif // UART_H