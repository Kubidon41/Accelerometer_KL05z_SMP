#include "MKL05Z4.h"   /* Device header */
#include "accelerometer.h"
void I2CInitialization(void);
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);
void i2c_wait(void);
void i2c_start(void);