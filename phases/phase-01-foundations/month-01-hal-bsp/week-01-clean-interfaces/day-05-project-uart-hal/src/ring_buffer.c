#include "ring_buffer.h"
#include <stddef.h>

#define BUFFER_SIZE 128
#define MAX_RING_BUFFERS 4 // Solo crearemos un máximo de 4 búferes

// Tu estructura, más una variable de estado (is_allocated) y un contador
struct RingBuffer
{
    uint8_t buffer[BUFFER_SIZE];
    size_t head;
    size_t tail;
    size_t count;
    bool is_allocated;
};

// Nuestro gestor de memoria sin usar malloc (Seguro para embebidos)
static struct RingBuffer buffer_pool[MAX_RING_BUFFERS] = {0};

ring_buffer_t *rb_create(void)
{
    for (int i = 0; i < MAX_RING_BUFFERS; i++)
    {
        if (!buffer_pool[i].is_allocated)
        {
            buffer_pool[i].is_allocated = true;
            buffer_pool[i].head = 0;
            buffer_pool[i].tail = 0;
            buffer_pool[i].count = 0;
            return (ring_buffer_t *)&buffer_pool[i];
        }
    }
    return NULL; // Pool lleno
}

bool rb_push(ring_buffer_t *self, uint8_t data)
{
    // Si el puntero es inválido o el contador alcanzó el límite, fallamos
    if (!self || self->count >= BUFFER_SIZE)
    {
        return false;
    }

    // 1. Guardamos el dato donde apunta 'head'
    self->buffer[self->head] = data;

    // 2. Avanzamos 'head' un paso (¡AQUÍ ESTÁ LA MAGIA CIRCULAR!)
    self->head = (self->head + 1) % BUFFER_SIZE;

    // 3. Aumentamos la cantidad de elementos esperando
    self->count++;

    return true;
}

bool rb_pop(ring_buffer_t *self, uint8_t *out_data)
{
    // Si el puntero es inválido, el destino es nulo, o no hay datos, fallamos
    if (!self || !out_data || self->count == 0)
    {
        return false;
    }

    // 1. Entregamos el dato donde apunta 'tail'
    *out_data = self->buffer[self->tail];

    // 2. Avanzamos 'tail' un paso
    self->tail = (self->tail + 1) % BUFFER_SIZE;

    // 3. Disminuimos la cantidad de elementos esperando
    self->count--;

    return true;
}