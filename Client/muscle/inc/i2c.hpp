#ifndef _I2C_
#define _I2C_

// #include <wiringPi.h>
// #include <wiringPiI2C.h>
// #include <stdio.h>
// #include <string.h>
// #include <errno.h>

// #include <unistd.h>

// #include <iostream>

#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define SIZE 4 * 1 + 1 //[bytes]

union Packet
{
    float data;
    char  bytes[4];
};

class I2c
{
private:
    const int _addr;
    const int _pin;

    int _fd;
    Packet _dataPack;
public:
    I2c(const int addr, const int pin);
    ~I2c();

    // void Write(const int num);
    void Write(const float num);
    // int Read();
    float Read(void);
};
#endif //_I2C_
