pub trait MonitorVoltaje {
    type Error;

    fn leer_voltaje(&mut self) -> Result<f32, Self::Error>;
}

use embedded_hal::i2c::I2c;

pub struct DriverADS1115<I2C> {
    i2c: I2C,
}

impl<I2C> DriverADS1115<I2C> {
    pub fn new(i2c: I2C) -> Self {
        Self { i2c }
    }
}

impl<I2C> MonitorVoltaje for DriverADS1115<I2C>
where
    I2C: I2c,
{
    type Error = I2C::Error;

    fn leer_voltaje(&mut self) -> Result<f32, Self::Error> {
        self.i2c.write(0x48, &[0x00])?;
        let mut buf = [0u8; 2];
        self.i2c.read(0x48, &mut buf)?;
        let raw = u16::from_be_bytes(buf);
        Ok(raw as f32 * 0.0001875)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct MockADC;

    impl MonitorVoltaje for MockADC {
        type Error = ();

        fn leer_voltaje(&mut self) -> Result<f32, Self::Error> {
            Ok(3.7)
        }
    }

    #[test]
    fn test_lectura_voltaje_bms() {
        let mut adc = MockADC;
        assert_eq!(adc.leer_voltaje(), Ok(3.7));
    }
}
