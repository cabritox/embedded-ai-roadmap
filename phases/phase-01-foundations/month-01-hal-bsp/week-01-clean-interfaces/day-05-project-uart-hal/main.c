#include "uart.h"
#include <stdio.h>
#include <string.h>

// Declaración de la función de inicialización del mock
void mock_init_loopback(uart_t **out_a, uart_t **out_b);

int main(void)
{
    printf("=== Iniciando Simulador de Hardware (Host Testing) ===\n\n");

    uart_t *uart_a;
    uart_t *uart_b;

    // El sistema levanta el hardware virtual (Cero cables)
    mock_init_loopback(&uart_a, &uart_b);

    // 1. UART A transmite un mensaje
    const char *mensaje = "Mensaje secreto enviado por UART A";
    uart_send(uart_a, (const uint8_t *)mensaje, strlen(mensaje));

    printf("\n[MAIN]: Leyendo datos desde el UART B...\n");

    // 2. UART B lee el mensaje (Desencolando el Ring Buffer)
    uint8_t byte;
    printf("[APP UART_B]: \"");
    while (uart_read(uart_b, &byte))
    {
        printf("%c", byte);
    }
    printf("\"\n\n");

    return 0;
}