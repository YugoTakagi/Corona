#ifndef _I2C_
#define _I2C_

#include <wiringPi.h>
#include <wiringPiI2C.h>

class I2c
{
private:
    const int _addr;
    const int _pin;

    int _fd;
public:
    I2c(const int addr, const int pin);
    ~I2c();

    void Write(const int num);
};
#endif //_I2C_
