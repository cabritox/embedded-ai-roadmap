// src/main.rs

/// 1. EL CONTRATO (Equivalente a la Vtable de C)
/// Obliga a cualquier hardware a implementar estas funciones.
pub trait Valvula {
    fn abrir(&mut self);
    fn cerrar(&mut self);
}

/// 2. EL HARDWARE (Equivalente al Puntero Opaco)
/// Los campos son privados por defecto. Nadie fuera de este archivo
/// puede modificar 'pin_fisico' ni corromper 'esta_abierta'.
pub struct ValvulaMock {
    pin_fisico: u8,
    esta_abierta: bool,
}

/// 3. CONSTRUCTOR (Equivalente a crear la instancia en C)
impl ValvulaMock {
    pub fn nueva(pin: u8) -> Self {
        ValvulaMock {
            pin_fisico: pin,
            esta_abierta: false, // Estado inicial seguro garantizado
        }
    }
}

/// 4. INYECCIÓN DEL CONTRATO AL HARDWARE (Static Dispatch)
/// El compilador verifica que no falte ninguna función del Trait.
impl Valvula for ValvulaMock {
    fn abrir(&mut self) {
        self.esta_abierta = true;
        println!("[Mock] Aplicando 12V al pin {}. Válvula ABIERTA.", self.pin_fisico);
    }

    fn cerrar(&mut self) {
        self.esta_abierta = false;
        println!("[Mock] Cortando voltaje al pin {}. Válvula CERRADA.", self.pin_fisico);
    }
}

/// 5. APLICACIÓN PRINCIPAL (Equivalente al main.c)
fn main() {
    println!("=== Iniciando Test de Traits en Rust ===\n");
    
    // Instanciamos el hardware. Usamos 'mut' porque su estado interno cambiará.
    let mut mi_valvula = ValvulaMock::nueva(4);

    // Usamos el contrato directamente
    mi_valvula.abrir();
    mi_valvula.cerrar();
    
    println!("\n=== Test Finalizado ===");
}