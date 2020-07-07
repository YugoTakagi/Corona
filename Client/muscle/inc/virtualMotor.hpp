#ifndef VIRTUALMOTOR
#define VIRTUALMOTOR

#include "../inc/i2c.hpp"
#include <iostream>

#define VELOCITY_MAX 100.0
#define VELOCITY_MIN -100.0

class VirtualMotor
{
private:
    int _num;
public:
    VirtualMotor(int num);
    ~VirtualMotor();

    bool SetVelocity(float velocity);
    bool SetDuty(int duty);
};
#endif//VIRTUALMOTOR