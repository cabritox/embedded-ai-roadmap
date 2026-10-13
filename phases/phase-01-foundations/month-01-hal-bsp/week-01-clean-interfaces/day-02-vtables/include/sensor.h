#ifndef SENSOR_H
#define SENSOR_H

#include <stdbool.h>

/**
 * @brief La Vtable (Tabla de Operaciones Virtuales).
 * Cualquier sensor (real o simulado) debe implementar estas funciones.
 */
typedef struct
{
    bool (*init)(void *ctx);
    bool (*read_temp)(void *ctx, float *out_temp);
} sensor_ops_t;

/* --- Funciones Auxiliares (Wrappers) para facilitar la lectura --- */

static inline bool sensor_init(const sensor_ops_t *ops, void *ctx)
{
    if (ops && ops->init)
        return ops->init(ctx);
    return false;
}

static inline bool sensor_read(const sensor_ops_t *ops, void *ctx, float *temp)
{
    if (ops && ops->read_temp)
        return ops->read_temp(ctx, temp);
    return false;
}

#endif // SENSOR_H