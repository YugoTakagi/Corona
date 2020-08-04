#include "../inc/virtualMotor.hpp"

VirtualMotor::VirtualMotor(const int pin)
:_pin(pin)
{
}

VirtualMotor::~VirtualMotor()
{
}

bool VirtualMotor::SetVelocity(I2c &i2c, float velocity)
{
    if (velocity < VELOCITY_MIN || VELOCITY_MAX < velocity)
    {
        if(velocity < VELOCITY_MIN)
        {
            std::cout << "motor velocity: " << VELOCITY_MIN << std::endl;
        }
        if(VELOCITY_MAX < velocity)
        {
            std::cout << "motor velocity: " << VELOCITY_MAX << std::endl;
        }
        return false;
    }
    else{
        std::cout << "motor velocity: " << velocity << std::endl;
        return true;
    }
}