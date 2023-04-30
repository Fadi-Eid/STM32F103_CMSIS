#ifndef I2C_H
#define I2C_H
#include <stdint.h>

#define I2C_FASTMODE 0x2D
#define I2C_STDMODE 0xB4

void I2C_Init(uint8_t i2c_num);
void I2C_Start(uint8_t i2c_num);
void I2C_Write(uint8_t i2c_num, uint8_t address, uint8_t data[], uint64_t length);
void I2C_Adress(uint8_t i2c_num, uint8_t address, uint8_t r_w);
void I2C_Data(uint8_t i2c_num, uint8_t data);
void I2C_Stop(uint8_t i2c_num);

#endif
