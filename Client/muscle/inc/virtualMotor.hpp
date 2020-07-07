#ifndef VIRTUALMOTOR
#define VIRTUALMOTOR

#include "../inc/i2c.hpp"
#include <iostream>

#define VELOCITY_MAX 100.0
#define VELOCITY_MIN -100.0

class VirtualMotor
{
private:
    I2c _i2c;
public:
    VirtualMotor(const int addr, const int pin);
    ~VirtualMotor();

    bool SetVelocity(float velocity);
    bool SetDuty(int duty);
};
#endif//VIRTUALMOTOR