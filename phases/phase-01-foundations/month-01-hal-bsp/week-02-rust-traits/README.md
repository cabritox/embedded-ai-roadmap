# Semana 2: Abstracciones Nativas en Rust y embedded-hal

## Objetivo de la Semana
Traducir los conceptos de separación de hardware aprendidos en C (Punteros Opacos, Vtables, Inyección de Instancias) a la sintaxis y filosofía de Rust. Aprenderemos a diseñar drivers que no saben si están corriendo en un ESP32, un STM32 o en tu propia computadora con Linux, utilizando el estándar de la industria `embedded-hal`.

---

### Día 1: El equivalente a Vtables: *Traits* en Rust
El puente conceptual. Entenderemos cómo Rust elimina la necesidad de crear tablas de punteros a funciones manualmente.
* **Teoría:** Diferencias entre la inyección de dependencias estática (Genéricos/Traits) vs dinámica (`dyn Trait` / Vtables).
* **Práctica:** Crear nuestro primer *Trait* (Contrato) para un actuador simple y aplicarlo a una estructura falsa (`Mock`).
* **Relación con C:** El concepto de `self` implícito y cómo Rust oculta la data por defecto (Adiós a los punteros opacos manuales).

### Día 2: El estándar de la industria: `embedded-hal`
¿Por qué escribir nuestros propios contratos cuando la comunidad ya lo hizo? Exploraremos la caja (`crate`) fundamental del ecosistema embebido en Rust.
* **Teoría:** Anatomía de `embedded-hal`. Análisis de los Traits estándar para I2C, SPI, UART y Pines digitales.
* **Práctica:** Importar `embedded-hal` en un proyecto nuevo usando Cargo e implementar un Trait de salida digital (`OutputPin`) en un hardware simulado.
* **El Ecosistema:** Cómo los fabricantes (Espressif, STMicroelectronics) implementan estos Traits para que tú no tengas que tocar los registros físicos.

### Día 3: Diseño de Drivers Agnósticos de la Plataforma
Crear un módulo que acepta cualquier pieza de hardware, siempre y cuando cumpla con el contrato eléctrico (Trait).
* **Teoría:** Uso de Genéricos (`<T>`) para inyectar hardware en una estructura sin amarrarnos a un microcontrolador específico.
* **Práctica:** Escribir un driver para un sensor I2C genérico. El driver no incluirá librerías del ESP32 ni del STM32; solo dependerá de `embedded-hal`.

### Día 4: Spec-Driven Development (SDD) y Contratos Estrictos en Rust
Evolución de la "ingeniería de prompts" temporal hacia el desarrollo industrial definitivo. La IA deja de ser un "creador de código libre" y pasa a ser un extractor de datos sometido a nuestras reglas arquitectónicas.
- **Teoría (El Flujo del Arquitecto):** Separación de poderes en SDD. El ingeniero humano define la frontera matemática y lógica (El Contrato / `Trait`) y la auditoría (El Host Test). La IA se limita a implementar los detalles de hardware físico (`Driver`).
- **Práctica:** Diseño de un `Trait` (`MonitorVoltaje`) exigiendo referencias mutables (`&mut self`) para interactuar con hardware real, y generación de una implementación I2C agnóstica para un ADC (ADS1115).
- **El Cambio de Paradigma:** No memorizar código; auditar y construir "trampas" de compilación que impidan a la IA (o a un programador junior) inyectar código acoplado, rompiendo la dependencia del microcontrolador específico.

### Día 5: Proyecto Integrador: Host Testing de un Driver Rust
El equivalente a nuestro Simulador UART de C, pero con herramientas modernas de Rust.
* **El Reto:** Ensamblar un driver agnóstico completo (ej. un sensor de temperatura simulado) y ejecutarlo nativamente en la terminal de Linux.
* **Herramientas:** Uso de `embedded-hal-mock` para crear hardware falso de I2C/SPI e inyectarlo en nuestro driver directamente en un entorno de pruebas unitarias de PC (`cargo test`).