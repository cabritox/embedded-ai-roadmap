#include <stdio.h>
#include "uart.h"

int main(void)
{
    printf("=========================================================\n");
    printf("  DEMO DÍA 03: Reentrancia e Inyección de Instancia (self)\n");
    printf("=========================================================\n\n");

    // 1. Instanciamos DOS puertos serie distintos
    // Ej: UART1 para un módulo GPS, UART2 para telemetría al PC
    uart_t *gps_uart = uart_create(1, 9600);
    uart_t *pc_uart = uart_create(2, 115200);

    if (!gps_uart || !pc_uart)
    {
        printf("Error fatal de inicialización.\n");
        return -1;
    }

    printf("\n--- Iniciando comunicaciones simultáneas ---\n");

    // 2. Transmitimos por el UART de telemetría (UART2)
    uint8_t msg_pc[] = "Iniciando sistema operativo...";
    uart_send(pc_uart, msg_pc, sizeof(msg_pc) - 1);

    // 3. Transmitimos comandos al GPS (UART1)
    uint8_t msg_gps[] = "AT+START";
    uart_send(gps_uart, msg_gps, sizeof(msg_gps) - 1);

    // 4. Transmitimos otra vez por telemetría
    uint8_t msg_pc2[] = "Coordenadas solicitadas con exito.";
    uart_send(pc_uart, msg_pc2, sizeof(msg_pc2) - 1);

    printf("\n--- Apagando sistema ---\n");

    // 5. Limpieza
    uart_destroy(gps_uart);
    uart_destroy(pc_uart);

    return 0;
}