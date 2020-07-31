#ifndef _VIRTUALSERVOMOTOR_
#define _VIRTUALSERVOMOTOR_

#include "../inc/i2c.hpp"
#include <iostream>
#include <math.h>

// #define VELOCITY_MAX        100.0
// #define VELOCITY_MIN        -100.0

#define SPRING_CONSTANT     1     // [N/m]
#define PULLEY_DIAMETER     0.015 // [m]
#define GEAR_RATIO          1     // [-]
#define RESOLUTION_OF_MOTOR 0.036 // [deg/pulse]
#define CONTROL_CYCLE       50    // [Hz]

class VirtualServoMotor
{
private:
    I2c   _i2c;
    float _movement;
    float _movementOfOnePalse;

    float _palsePerSec;
public:
    VirtualServoMotor(const int addr, const int pin);
    ~VirtualServoMotor();

    // bool SetVelocity(float velocity);
    // bool SetDuty(int duty);
    void SetRefForse(float refForse);
};
#endif //_VIRTUALSERVOMOTOR_