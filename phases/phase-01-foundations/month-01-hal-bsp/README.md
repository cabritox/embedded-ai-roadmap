# Mes 01: Abstracción de Hardware y Capas (HAL / BSP)

##  Objetivo del Mes
Diseñar e implementar arquitecturas de firmware modulares y desacopladas de la plataforma de hardware. Durante este mes establecerás los cimientos para escribir código portátil en C y Rust, probar firmware directamente en el equipo anfitrión (*Host Testing*) y utilizar la Inteligencia Artificial para acelerar el análisis de *datasheets* y la generación de drivers bajo contratos de interfaz estrictos.

---

## 🗺️ Mapa de Semanas

## Semana 01
**Tema central:** **Interfaces Limpias y Aislamiento de Hardware** 
**Entregable:** Punteros opacos, *Vtables* en C, inyección de instancia (`self`) y drivers sin variables globales.

## Semana 02
**Tema central:** **Arquitecturas Event-Driven y Máquinas de Estados** 
**Entregable:** Implementación de FSM planas y Jerárquicas (HSM) en *bare-metal* sin asignación dinámica de memoria.

## Semana 03
**Tema central:** **Host Testing, Análisis Estático y Prompting Técnico** 
**Entregable:** Mocks con Unity/CMock, pipeline con `clang-tidy`/`cppcheck` y prompts estructurados para *datasheets*.

## Semana 04
**Tema central:** **Proyecto Integrador del Mes 1** 
**Entregable:** Driver HAL modular completo + FSM ejecutable en PC y validado mediante pruebas unitarias automáticas.

---

## 🏗️ Arquitectura de Referencia (Modelo en Capas)

```text
+-------------------------------------------------------------+
|                Lógica de la Aplicación                      |
+-------------------------------------------------------------+
                              |  (Llama a interfaces abstractas)
+-------------------------------------------------------------+
|    Capa de Abstracción de Hardware (HAL) / Vtable API      |
+-------------------------------------------------------------+
                              |  (Implementación concreta)
+-------------------------------------------------------------+
|       Board Support Package (BSP) / Registros / Emulación   |
+-------------------------------------------------------------+