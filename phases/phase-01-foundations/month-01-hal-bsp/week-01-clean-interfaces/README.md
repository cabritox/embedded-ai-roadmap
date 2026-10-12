
# Semana 01: Diseño de Interfaces Limpias y Aislamiento de Hardware en C

## 🎯 Resumen y Objetivos
El objetivo principal de esta semana es dominar las técnicas de diseño orientado a objetos en C para eliminar el acoplamiento entre el software de aplicación y los registros del silicio. Aprenderás a construir interfaces opacas, utilizar tablas de operaciones polimórficas (*Vtables*) y diseñar contratos técnicos claros que permitan a las herramientas de IA generar código de producción seguro.

## 🗓️ Plan de Trabajo Diario

### Día 01: Encapsulamiento Real con Punteros Opacos (*Opaque Pointers*)
- **Foco Técnico:** Ocultar detalles de implementación mediante *Forward Declarations* y el patrón Pimpl (*Pointer to Implementation*).
- **Entregable:** Driver GPIO con tipo opaco `gpio_t*`, impidiendo que el cliente acceda directamente a miembros o registros.
- **Ruta:** `day-01-opaque-pointers/`

### Día 02: Polimorfismo en C mediante Tablas de Operaciones (*Vtables*)
- **Foco Técnico:** Estructuras con punteros a funciones para intercambiar implementaciones de hardware en tiempo de ejecución (ej. interfaz física vs. interfaz *Mock*).
- **Entregable:** Interfaz abstracta `sensor_ops_t` aplicada a un driver de temperatura.
- **Ruta:** `day-02-vtables/`

### Día 03: Reentrancia e Inyección de Instancia (`self`)
- **Foco Técnico:** Eliminación de variables globales en la capa HAL passing el contexto `self` como primer parámetro en cada función.
- **Entregable:** Driver UART multicanal capaz de gestionar múltiples instancias (`UART1`, `UART2`) simultáneamente sin colisión de estado.
- **Ruta:** `day-03-instance-injection/`

### Día 04: Contratos de Interfaz y Prompting para IA
- **Foco Técnico:** Definición estricta de contratos en `.h` con especificaciones Doxygen, restricciones de memoria y tipos de retorno para guiar a la IA.
- **Entregable:** Cabecera `.h` utilizada como prompt para que la IA genere el archivo `.c` correspondiente sin cambiar firmas.
- **Ruta:** `day-04-ai-contracts/`

### Día 05: Proyecto Integrador de la Semana — Driver HAL de Bus UART
- **Foco Técnico:** Combinación de Punteros Opacos, Vtables e Inyección de Instancia para crear un bus de comunicación simulado en PC con buffers circulares.
- **Entregable:** Proyecto completo con CMake ejecutable en Host y batería de pruebas básicas.
- **Ruta:** `day-05-project-uart-hal/`