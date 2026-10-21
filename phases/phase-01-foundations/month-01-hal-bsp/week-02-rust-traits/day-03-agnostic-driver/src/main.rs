use core::convert::Infallible;
use embedded_hal::i2c::{ErrorType, I2c, Operation};

/// =================================================================
/// 1. TU DRIVER (Lógica agnóstica. Cero dependencias de hardware)
/// =================================================================

// La estructura acepta un genérico <I2C>
pub struct SensorGenerico<I2C> {
    bus_i2c: I2C,
    direccion: u8,
}

// Implementamos los métodos. 
// "where I2C: I2c<Error = E>" es la restricción: el genérico debe cumplir el contrato.
impl<I2C, E> SensorGenerico<I2C>
where
    I2C: I2c<Error = E>,
{
    pub fn nuevo(bus_i2c: I2C, direccion: u8) -> Self {
        Self { bus_i2c, direccion }
    }

    // Lógica pura de negocio: Para leer el ID del chip, escribimos el registro 0xD0
    // y luego leemos la respuesta en la misma transacción (write_read).
    pub fn leer_chip_id(&mut self) -> Result<u8, E> {
        let mut buffer = [0u8; 1];
        let registro = [0xD0]; 
        
        self.bus_i2c.write_read(self.direccion, &registro, &mut buffer)?;
        
        Ok(buffer[0])
    }
}

/// =================================================================
/// 2. EL HARDWARE MOCK (Tu simulación para PC)
/// =================================================================

struct I2cSimulado;

impl ErrorType for I2cSimulado {
    type Error = Infallible;
}

// Firmamos el contrato I2C de embedded-hal
impl I2c for I2cSimulado {
    fn read(&mut self, _addr: u8, _read: &mut [u8]) -> Result<(), Self::Error> { Ok(()) }
    fn write(&mut self, _addr: u8, _write: &[u8]) -> Result<(), Self::Error> { Ok(()) }
    
    // Este es el método que nuestro driver utiliza
    fn write_read(&mut self, addr: u8, write: &[u8], read: &mut [u8]) -> Result<(), Self::Error> {
        println!("[Mock I2C HW] -> Dispositivo 0x{:02X} solicitó lectura del registro 0x{:02X}", addr, write[0]);
        // Simulamos que el hardware respondió con el ID 0x42
        read[0] = 0x42; 
        Ok(())
    }
    
    fn transaction(&mut self, _addr: u8, _ops: &mut [Operation<'_>]) -> Result<(), Self::Error> { Ok(()) }
}

/// =================================================================
/// 3. APLICACIÓN PRINCIPAL (Inyección de dependencias)
/// =================================================================
fn main() {
    println!("=== Test Driver Agnóstico I2C ===\n");

    // 1. Levantamos el hardware físico (en este caso, la simulación)
    let bus_fisico = I2cSimulado;

    // 2. Inyectamos el hardware en el driver (Dirección I2C: 0x76)
    let mut mi_sensor = SensorGenerico::nuevo(bus_fisico, 0x76);

    // 3. Consumimos el driver
    match mi_sensor.leer_chip_id() {
        Ok(id) => println!("[App] Éxito: Chip ID leído = 0x{:02X}", id),
        Err(_) => println!("[App] Error de comunicación I2C"),
    }
}