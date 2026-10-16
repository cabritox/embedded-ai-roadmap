#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Puntero opaco para encapsular la estructura del Búfer Circular.
 */
typedef struct RingBuffer ring_buffer_t;

/**
 * @brief Instancia un nuevo Búfer Circular desde el pool de memoria estático.
 * @return ring_buffer_t* Puntero a la instancia, o NULL si no hay memoria.
 */
ring_buffer_t *rb_create(void);

/**
 * @brief Inserta un byte en el búfer (Sala de espera).
 * @param self Instancia del búfer.
 * @param data Byte a insertar.
 * @return true si se insertó con éxito, false si el búfer está lleno.
 */
bool rb_push(ring_buffer_t *self, uint8_t data);

/**
 * @brief Extrae el byte más antiguo del búfer (FIFO).
 * @param self Instancia del búfer.
 * @param out_data Puntero donde se depositará el byte extraído.
 * @return true si se extrajo un byte, false si el búfer está vacío.
 */
bool rb_pop(ring_buffer_t *self, uint8_t *out_data);

#endif // RING_BUFFER_H