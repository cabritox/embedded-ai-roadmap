#include "uart.h"
#include "ring_buffer.h"
#include <stdio.h>

// Contexto privado del hardware falso
typedef struct
{
    ring_buffer_t *rx_buffer;
    ring_buffer_t *tx_buffer; // Apunta al RX del otro UART
    const char *name;
} mock_ctx_t;

// Implementación de las funciones de la Vtable
static bool mock_transmit(void *ctx, const uint8_t *data, size_t length)
{
    mock_ctx_t *m = (mock_ctx_t *)ctx;
    printf("[%s_HW]: Transmitiendo %zu bytes...\n", m->name, length);
    for (size_t i = 0; i < length; i++)
    {
        if (!rb_push(m->tx_buffer, data[i]))
            return false;
    }
    return true;
}

static bool mock_receive(void *ctx, uint8_t *out_data)
{
    mock_ctx_t *m = (mock_ctx_t *)ctx;
    return rb_pop(m->rx_buffer, out_data);
}

// La Vtable concreta
static const uart_ops_t mock_ops = {
    .transmit = mock_transmit,
    .receive = mock_receive};

// Instancias estáticas del contexto
static mock_ctx_t ctx_a = {.name = "UART_A"};
static mock_ctx_t ctx_b = {.name = "UART_B"};

// Función para inicializar el par cruzado
void mock_init_loopback(uart_t **out_a, uart_t **out_b)
{
    ring_buffer_t *rb_a = rb_create();
    ring_buffer_t *rb_b = rb_create();

    // Cruzamos los cables TX -> RX
    ctx_a.rx_buffer = rb_a;
    ctx_a.tx_buffer = rb_b;

    ctx_b.rx_buffer = rb_b;
    ctx_b.tx_buffer = rb_a;

    *out_a = uart_create(&mock_ops, &ctx_a);
    *out_b = uart_create(&mock_ops, &ctx_b);
}