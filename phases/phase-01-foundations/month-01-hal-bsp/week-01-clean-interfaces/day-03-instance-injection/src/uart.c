#include "uart.h"
#include <stdio.h>

#define MAX_UART_INSTANCES 3
#define UART_TX_BUFFER_SIZE 128

/**
 * @brief Estructura privada. El estado VIVE AQUÍ, no en variables globales.
 */
struct UARTDevice
{
    uint8_t port_number;
    uint32_t baudrate;

    // Cada instancia tiene su propio buffer de transmisión aislado
    uint8_t tx_buffer[UART_TX_BUFFER_SIZE];
    bool is_allocated;
};

// Pool de memoria estático (Sin malloc)
static struct UARTDevice uart_pool[MAX_UART_INSTANCES] = {0};

uart_t *uart_create(uint8_t port_number, uint32_t baudrate)
{
    for (int i = 0; i < MAX_UART_INSTANCES; i++)
    {
        if (!uart_pool[i].is_allocated)
        {
            uart_pool[i].is_allocated = true;
            uart_pool[i].port_number = port_number;
            uart_pool[i].baudrate = baudrate;

            printf("[HAL UART]: Instancia UART%d creada a %u bps (Slot %d)\n",
                    port_number, baudrate, i);
            return (uart_t *)&uart_pool[i];
        }
    }
    printf("[HAL UART]: Error - No hay instancias disponibles en el pool.\n");
    return NULL;
}

uart_status_t uart_send(uart_t *self, const uint8_t *data, uint16_t length)
{
    // 1. Validación estricta de la instancia
    if (!self || !self->is_allocated || !data || length == 0)
    {
        return UART_ERR_INVALID_ARG;
    }

    if (length > UART_TX_BUFFER_SIZE)
    {
        printf("[HAL UART%d]: Error - Mensaje demasiado largo.\n", self->port_number);
        return UART_ERR_NO_MEMORY;
    }

    // 2. Copia segura al buffer PRIVADO de ESTA instancia
    for (uint16_t i = 0; i < length; i++)
    {
        self->tx_buffer[i] = data[i];
    }

    // 3. Simulación de transmisión por hardware
    printf("[HW_REG UART%d]: Transmitiendo %d bytes a %u bps -> \"",
            self->port_number, length, self->baudrate);

    for (uint16_t i = 0; i < length; i++)
    {
        printf("%c", self->tx_buffer[i]);
    }
    printf("\"\n");

    return UART_OK;
}

void uart_destroy(uart_t *self)
{
    if (!self || !self->is_allocated)
        return;

    printf("[HAL UART]: Instancia UART%d destruida y liberada.\n", self->port_number);
    self->is_allocated = false;
}