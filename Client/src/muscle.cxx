#include "../inc/muscle.hpp"

Muscle::Muscle(c_float dt, c_float pGain, c_float iGain, c_float dGain)
:_pid(dt)
{
    _pid.SetGain(pGain, iGain, dGain);
    _force = new float[3];
}

Muscle::~Muscle()
{
    delete[] _force;
}

float* Muscle::Stretch(c_float ref)
{
    _force[0] = ref;
    _force[1] = MeasureForce();
    _force[2] = _pid.run(_force[0], _force[1]);
    _motor.SetVelocity(_force[2]);
    return _force;
}

float Muscle::MeasureForce()
{
    _measuredForce = 0.0;
    // run code


    // ~run code
    return _measuredForce;
}

