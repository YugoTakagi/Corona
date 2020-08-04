#include "../inc/muscle.hpp"

Muscle::Muscle(int addr, int pin, c_float dt, c_float pGain, c_float iGain, c_float dGain)
:_pid(dt, pGain, iGain, dGain)
,_i2c(addr, pin)
,_motor(pin)
,_pGain(pGain)
,_iGain(iGain)
,_dGain(dGain)
{
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
    std::cout << "pid: " << _force[ASCAL] << std::endl;

    _motor.SetVelocity(_i2c, _force[ASCAL]);
    return _force;
}

float Muscle::MeasureForce()
{
    _measuredForce = 0.0;
    // run code
    _i2c.Read();

    // ~run code
    return _measuredForce;
}

void Muscle::GetGain(float *buff, size_t size) const
{   
    if (( size/sizeof(float) ) != 3) exit(0);
    buff[P] = _pGain;
    buff[I] = _iGain;
    buff[D] = _dGain;
}
