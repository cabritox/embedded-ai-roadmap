#include <stdio.h>
#include "sensor.h"
#include "mock_sensor.h"

// Lógica de negocio (Agnóstica al hardware)
void app_control_clima(const sensor_ops_t *sensor_ops, void *sensor_ctx)
{
    printf("--- Iniciando Tarea de Control de Clima ---\n");

    if (!sensor_init(sensor_ops, sensor_ctx))
    {
        printf("Error fatal: No se pudo inicializar el sensor.\n");
        return;
    }

    float temperatura = 0.0f;

    // Simulamos un bucle de control en tiempo real (3 iteraciones)
    for (int i = 1; i <= 3; i++)
    {
        printf("\nCiclo %d:\n", i);
        if (sensor_read(sensor_ops, sensor_ctx, &temperatura))
        {
            if (temperatura > 26.0f)
            {
                printf("  [Lógica de App] ALARMA: Temp muy alta (%.2f). ¡Activando relé de ventilación!\n", temperatura);
            }
            else
            {
                printf("  [Lógica de App] Temperatura estable (%.2f). Todo en orden.\n", temperatura);
            }
        }
    }
}

int main(void)
{
    printf("==================================================\n");
    printf("  DEMO DÍA 02: Polimorfismo en C mediante Vtables \n");
    printf("==================================================\n\n");

    // En la fase de inicio (Boot), inyectamos la implementación que queremos usar.
    // Como estamos en PC, inyectamos el Mock. En la placa física, inyectaríamos el I2C.
    const sensor_ops_t *ops_a_usar = mock_sensor_get_ops();
    void *contexto_a_usar = mock_sensor_get_ctx();

    app_control_clima(ops_a_usar, contexto_a_usar);

    return 0;
}