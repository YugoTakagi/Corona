#include "../inc/muscle.hpp"

Muscle::Muscle(c_float dt, c_float pGain, c_float iGain, c_float dGain)
:_pid(dt)
,_pGain(pGain)
,_iGain(iGain)
,_dGain(dGain)
{
    _pid.SetGain(pGain, iGain, dGain);
    _force = new float[3];
}

Muscle::~Muscle()
{
    delete[] _force;
}

float* Muscle::Stretch(c_float &ref)
{
    _force[ASREF] = ref;
    _force[ASMES] = MeasureForce();

    _force[ASCAL] = _pid.run(_force[ASREF], _force[ASMES]);

    _motor.SetVelocity(_force[ASCAL]);
    return _force;
}

float Muscle::MeasureForce()
{
    _measuredForce = 0.0;
    // run code


    // ~run code
    return _measuredForce;
}

void Muscle::GetGain(float buff[3]) const
{   
    buff[P] = _pGain;
    buff[I] = _iGain;
    buff[D] = _dGain;
}