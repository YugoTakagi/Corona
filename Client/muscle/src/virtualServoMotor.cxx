#include "../inc/virtualServoMotor.hpp"

VirtualServoMotor::VirtualServoMotor(const int addr, const int pin)
:_i2c(addr, pin)
{
}

VirtualServoMotor::~VirtualServoMotor()
{
}

void VirtualServoMotor::SetRefForse(float refForce)
{
    // if (velocity < VELOCITY_MIN || VELOCITY_MAX < velocity)
    // {
    //     if(velocity < VELOCITY_MIN)
    //     {
    //         std::cout << "motor velocity: " << VELOCITY_MIN << std::endl;
    //     }
    //     if(VELOCITY_MAX < velocity)
    //     {
    //         std::cout << "motor velocity: " << VELOCITY_MAX << std::endl;
    //     }
    //     return false;
    // }
    // else{
    //     std::cout << "motor velocity: " << velocity << std::endl;
    //     return true;
    // }

    _movement = refForce / SPRING_CONSTANT;
    _movementOfOnePalse = (M_PI*PULLEY_DIAMETER) / (GEAR_RATIO*RESOLUTION_OF_MOTOR);

    _palsePerSec = _movement / _movementOfOnePalse;
    _i2c.Write(_palsePerSec);
}