#include "uart.h"

struct UARTDevice
{
    const uart_ops_t *ops;
    void *ctx;
};

// Pool simple para el ejemplo
static struct UARTDevice uart_pool[2];
static int uart_count = 0;

uart_t *uart_create(const uart_ops_t *ops, void *ctx)
{
    if (uart_count >= 2)
        return NULL;
    uart_pool[uart_count].ops = ops;
    uart_pool[uart_count].ctx = ctx;
    return &uart_pool[uart_count++];
}

bool uart_send(uart_t *self, const uint8_t *data, size_t length)
{
    if (!self || !self->ops->transmit)
        return false;
    return self->ops->transmit(self->ctx, data, length);
}

bool uart_read(uart_t *self, uint8_t *out_data)
{
    if (!self || !self->ops->receive)
        return false;
    return self->ops->receive(self->ctx, out_data);
}