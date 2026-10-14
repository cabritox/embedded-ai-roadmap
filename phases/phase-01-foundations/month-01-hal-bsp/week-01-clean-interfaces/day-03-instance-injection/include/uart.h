#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Códigos de estado del driver UART.
 */
typedef enum
{
    UART_OK = 0,
    UART_ERR_INVALID_ARG,
    UART_ERR_NO_MEMORY,
    UART_ERR_BUSY
} uart_status_t;

/**
 * @brief Tipo opaco para la instancia del UART.
 */
typedef struct UARTDevice uart_t;

/**
 * @brief Instancia un nuevo puerto UART.
 *
 * @param port_number Número del hardware físico (ej. 1 para UART1, 2 para UART2).
 * @param baudrate Velocidad de transmisión (ej. 115200).
 * @return uart_t* Puntero a la instancia aislada, o NULL si falla.
 */
uart_t *uart_create(uint8_t port_number, uint32_t baudrate);

/**
 * @brief Envía un buffer de datos a través del UART.
 *
 * @param self Puntero a la instancia específica que debe transmitir.
 * @param data Puntero a los bytes a enviar.
 * @param length Cantidad de bytes.
 * @return uart_status_t Estado de la operación.
 */
uart_status_t uart_send(uart_t *self, const uint8_t *data, uint16_t length);

/**
 * @brief Libera la instancia del UART.
 *
 * @param self Puntero a la instancia a liberar.
 */
void uart_destroy(uart_t *self);

#endif // UART_H