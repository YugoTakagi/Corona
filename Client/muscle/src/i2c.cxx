#include "../inc/i2c.hpp"

I2c::I2c(const int addr, const int pin)
:_addr(addr)
,_pin(pin)
{
    wiringPiSetupGpio();
    pinMode(_pin, INPUT);

    /* WHO AM I */
    _fd = wiringPiI2CSetup(_addr);
}

I2c::~I2c()
{
}

void I2c::Write(const int num)
{
    wiringPiI2CWrite(_fd, num);
}

void I2c::Read()
{
    
}
