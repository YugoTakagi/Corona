#ifndef _VIRTUALMOTOR_
#define _VIRTUALMOTOR_

#include "../inc/i2c.hpp"
#include <iostream>

#define VELOCITY_MAX 100.0
#define VELOCITY_MIN -100.0

class VirtualMotor
{
private:
    int _pin;
public:
    VirtualMotor(const int pin);
    ~VirtualMotor();

    bool SetVelocity(I2c &i2c, float velocity);
    bool SetDuty(I2c &i2c, int duty);
};
#endif //_VIRTUALMOTOR_
