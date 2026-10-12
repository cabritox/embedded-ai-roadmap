#include <stdio.h>
#include "gpio.h"

int main(void)
{
    printf("==================================================\n");
    printf("  DEMO DÍA 01: HAL GPIO con Punteros Opacos (C11) \n");
    printf("==================================================\n\n");

    // 1. Instanciar periféricos
    gpio_t *led_status = gpio_create(13, GPIO_MODE_OUTPUT);
    gpio_t *button = gpio_create(5, GPIO_MODE_INPUT);

    if (!led_status || !button)
    {
        printf("Error fatal: No se pudieron instanciar los periféricos.\n");
        return -1;
    }

    // 2. Intento de violación de encapsulamiento (Si descomentas esto, el compilador falla)
    // led_status->pin_number = 10; // Error: dereferencing pointer to incomplete type 'struct GPIODevice'

    // 3. Probar escritura de salida
    printf("\n--- Test 1: Encender LED Status ---\n");
    gpio_write(led_status, GPIO_STATE_HIGH);

    // 4. Probar conmutación (Toggle)
    printf("\n--- Test 2: Conmutar LED Status (Toggle) ---\n");
    gpio_toggle(led_status);

    // 5. Lectura de estado
    printf("\n--- Test 3: Leer Estado de Botón ---\n");
    gpio_state_t button_state;
    gpio_read(button, &button_state);

    // 6. Validación de error: Intentar escribir en entrada
    printf("\n--- Test 4: Escribir en un Pin de Entrada (Debe Fallar) ---\n");
    gpio_status_t status = gpio_write(button, GPIO_STATE_HIGH);
    if (status != GPIO_STATUS_OK)
    {
        printf("Respuesta correcta del HAL: Operación rechazada.\n");
    }

    // 7. Liberar recursos del pool
    printf("\n--- Test 5: Destrucción de Instancias ---\n");
    gpio_destroy(led_status);
    gpio_destroy(button);

    printf("\nPrueba ejecutada correctamente con cero fuga de abstracción.\n");
    return 0;
}