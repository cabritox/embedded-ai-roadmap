// Importamos los contratos oficiales (La Capa Intermedia)
use embedded_hal::digital::{ErrorType, OutputPin};
use core::convert::Infallible;

/// ==========================================
/// CAPA INFERIOR: El Hardware (Nuestro Mock)
/// ==========================================

// 1. Puntero Opaco (Estado físico)
pub struct LedMock {
    pin_number: u8,
    is_on: bool,
}

impl LedMock {
    pub fn nuevo(pin: u8) -> Self {
        LedMock { pin_number: pin, is_on: false }
    }
}

// 2. Manejo de Errores Obligatorio
// embedded-hal exige que digamos qué tipo de error puede devolver nuestro hardware.
// Como es un simulador en PC, nunca fallará físicamente, así que usamos 'Infallible'.
impl ErrorType for LedMock {
    type Error = Infallible;
}

// 3. Firmamos el contrato OutputPin de embedded-hal
impl OutputPin for LedMock {
    fn set_high(&mut self) -> Result<(), Self::Error> {
        self.is_on = true;
        println!("[Hardware] Pin {} configurado a ALTO (3.3V)", self.pin_number);
        Ok(()) // Retornamos un "Todo salió bien"
    }

    fn set_low(&mut self) -> Result<(), Self::Error> {
        self.is_on = false;
        println!("[Hardware] Pin {} configurado a BAJO (0V)", self.pin_number);
        Ok(())
    }
}

/// ==========================================
/// CAPA SUPERIOR: Lógica de Negocio (Tu Driver)
/// ==========================================

// ¡Esta es la magia! Esta función NO sabe qué es un LedMock ni un ESP32.
// Solo exige: "Dame cualquier cosa (P) que cumpla con el contrato OutputPin".
fn parpadear_led<P: OutputPin>(pin: &mut P) -> Result<(), P::Error> {
    println!("--- Iniciando parpadeo ---");
    pin.set_high()?; // El '?' propaga el error automáticamente si el hardware falla
    pin.set_low()?;
    Ok(())
}

/// ==========================================
/// EL PANEL DE CONTROL (main.c equivalente)
/// ==========================================
fn main() {
    println!("=== Test de embedded-hal ===\n");

    // Instanciamos nuestro hardware falso (Capa Inferior)
    let mut mi_led_simulado = LedMock::nuevo(13);

    // Le pasamos el hardware a la lógica genérica (Capa Superior)
    // El Static Dispatch de Rust enlaza todo con costo cero de CPU.
    let _ = parpadear_led(&mut mi_led_simulado);

    println!("\n=== Test Finalizado ===");
}