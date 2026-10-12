#include "gpio.h"
#include <stdio.h>

/**
 * @brief Capacidad máxima del pool de memoria estática para GPIOs.
 */
#define MAX_GPIO_INSTANCES 4

/**
 * @brief Definición privada de la estructura del periférico GPIO.
 * @note Oculta totalmente al cliente. Solo es accesible dentro de este .c.
 */
struct GPIODevice
{
    uint8_t pin_number;
    gpio_mode_t mode;
    gpio_state_t state;
    bool is_allocated;
};

/**
 * @brief Pool de asignación estática (Sección BSS/DATA).
 * Asigna memoria fija en tiempo de compilación para evitar el uso del Heap/malloc.
 */
static struct GPIODevice gpio_pool[MAX_GPIO_INSTANCES] = {0};

gpio_t *gpio_create(uint8_t pin_number, gpio_mode_t mode)
{
    for (size_t i = 0; i < MAX_GPIO_INSTANCES; i++)
    {
        if (!gpio_pool[i].is_allocated)
        {
            gpio_pool[i].is_allocated = true;
            gpio_pool[i].pin_number = pin_number;
            gpio_pool[i].mode = mode;
            gpio_pool[i].state = GPIO_STATE_LOW;

            printf("[HAL GPIO Driver]: Pin %d instanciado en pool estático (Slot #%zu).\n",
                   pin_number, i);

            return (gpio_t *)&gpio_pool[i];
        }
    }

    printf("[HAL GPIO Driver Error]: Pool lleno. No se pudo instanciar el Pin %d.\n", pin_number);
    return NULL;
}

gpio_status_t gpio_write(gpio_t *self, gpio_state_t state)
{
    if (!self || !self->is_allocated)
    {
        return GPIO_STATUS_ERROR_INVALID_ARG;
    }

    if (self->mode == GPIO_MODE_INPUT)
    {
        printf("[HAL GPIO Warning]: Intento de escritura en Pin %d configurado como ENTRADA.\n",
               self->pin_number);
        return GPIO_STATUS_ERROR_INVALID_ARG;
    }

    self->state = state;
    printf("[HAL Hardware HW_REG]: Pin %d -> Estado: %s\n",
           self->pin_number,
           (state == GPIO_STATE_HIGH) ? "HIGH (3.3V)" : "LOW (0V)");

    return GPIO_STATUS_OK;
}

gpio_status_t gpio_read(const gpio_t *self, gpio_state_t *out_state)
{
    if (!self || !self->is_allocated || !out_state)
    {
        return GPIO_STATUS_ERROR_INVALID_ARG;
    }

    *out_state = self->state;
    printf("[HAL Hardware HW_REG]: Lectura Pin %d -> %s\n",
           self->pin_number,
           (self->state == GPIO_STATE_HIGH) ? "HIGH" : "LOW");

    return GPIO_STATUS_OK;
}

gpio_status_t gpio_toggle(gpio_t *self)
{
    if (!self || !self->is_allocated)
    {
        return GPIO_STATUS_ERROR_INVALID_ARG;
    }

    gpio_state_t new_state = (self->state == GPIO_STATE_LOW) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
    return gpio_write(self, new_state);
}

void gpio_destroy(gpio_t *self)
{
    if (!self || !self->is_allocated)
    {
        return;
    }

    printf("[HAL GPIO Driver]: Pin %d liberado del pool estático.\n", self->pin_number);
    self->is_allocated = false;
    self->state = GPIO_STATE_LOW;
}