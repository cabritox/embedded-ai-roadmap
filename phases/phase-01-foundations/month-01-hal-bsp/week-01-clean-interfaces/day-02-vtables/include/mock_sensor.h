#ifndef MOCK_SENSOR_H
#define MOCK_SENSOR_H

#include "sensor.h"

// Funciones para obtener la Vtable y el contexto del sensor de mentira
const sensor_ops_t *mock_sensor_get_ops(void);
void *mock_sensor_get_ctx(void);

#endif // MOCK_SENSOR_H