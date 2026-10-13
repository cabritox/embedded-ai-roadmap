#include "mock_sensor.h"
#include <stdio.h>

// El contexto (estado privado) de nuestro sensor falso
typedef struct
{
    float current_temp;
    bool is_initialized;
} mock_context_t;

// Instancia estática de nuestro sensor
static mock_context_t my_mock_instance = {
    .current_temp = 25.0f,
    .is_initialized = false};

/* --- Implementación de las funciones del Contrato --- */

static bool mock_init(void *ctx)
{
    mock_context_t *m = (mock_context_t *)ctx;
    m->is_initialized = true;
    printf("[Driver MOCK]: Hardware simulado inicializado correctamente.\n");
    return true;
}

static bool mock_read(void *ctx, float *out_temp)
{
    mock_context_t *m = (mock_context_t *)ctx;
    if (!m->is_initialized)
        return false;

    *out_temp = m->current_temp;
    m->current_temp += 1.5f; // Simulamos que el hardware se calienta en cada lectura

    printf("[Driver MOCK]: Leyendo ADC simulado -> %.2f °C\n", *out_temp);
    return true;
}

/* --- Construcción de la Vtable --- */

static const sensor_ops_t mock_ops = {
    .init = mock_init,
    .read_temp = mock_read};

/* --- Exposición hacia el exterior --- */

const sensor_ops_t *mock_sensor_get_ops(void)
{
    return &mock_ops;
}

void *mock_sensor_get_ctx(void)
{
    return &my_mock_instance;
}