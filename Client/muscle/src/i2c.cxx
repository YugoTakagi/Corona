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

void I2c::Write(const float val)
{
    _dataPack.data = val;
    write(_fd, _dataPack.bytes, SIZE);
}

float I2c::Read()
{
    _dataPack.data = 0.0;
    read(_fd, _dataPack.bytes, SIZE);

    return _dataPack.data;
}

// void I2c::Write(const int val)
// {
//     if(val < 0)
//     {
//         // int tempW[2] = {0, -1*val};
//         // write(fd, tempW, 2);
//         wiringPiI2CWrite(_fd, 0);
//         wiringPiI2CWrite(_fd, -1*val);
//     }
//     else
//     {
//         wiringPiI2CWrite(_fd, 1);
//         wiringPiI2CWrite(_fd, val);
//     }
// }

// int I2c::Read()
// {
//     // printf("read : %d\n", wiringPiI2CReadReg16(fd, 22));
//     // printf("read : %d\n", wiringPiI2CRead(fd));

//     // できた理由が分からない
//     int temp[2] = {0};
//     int f = read(_fd, temp, 2);
//     printf("read : %d\n", temp[0]);
//     return f;
// }