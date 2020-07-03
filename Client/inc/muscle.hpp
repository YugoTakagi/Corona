#ifndef MUSCLE
#define MUSCLE

#include "pid.hpp"
#include "virtualMotor.hpp"

typedef const float c_float;

// PIDコントローラにより筋張力[N]を算出し, モータを制御します.
// Example:
//      Muscle vasInt(dt, pGain, iGain, dGain);
//      for(float reff : reffs)
//      {
//          vasInt.Stretch(reff, mesf)
//      }    
class Muscle
{
private:
    PidControler _pid;
    VirtualMotor _motor;
    
    float* _force;
    float _measuredForce;
    float* _gain;
public:
    Muscle(c_float dt, c_float pGain, c_float iGain, c_float dGain);
    ~Muscle();

    float* Stretch(c_float ref);
    float MeasureForce();
    float* ReakGain();
};

#endif//MUSCLE