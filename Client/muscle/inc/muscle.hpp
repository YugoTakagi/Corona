#ifndef _MUSCLE_
#define _MUSCLE_

#include "pid.hpp"
#include "virtualMotor.hpp"

typedef const float c_float;

#define P 0
#define I 1
#define D 2

#define ASREF 0 // as reference
#define ASMES 1 // as measured
#define ASCAL 2 // as calc

// PIDコントローラにより筋張力[N]を算出し, モータを制御します.
// Example:
//      Muscle vasInt(dt, pGain, iGain, dGain);
//      for(float refF : refFArray)
//      {
//          vasInt.Stretch(refF)
//      }    
class Muscle
{
private:
    PidControler _pid;
    VirtualMotor _motor;

    c_float      _pGain;
    c_float      _iGain;
    c_float      _dGain;

    float*       _force;
    float        _measuredForce;
public:
    Muscle
    (
        int addr, int pin, 
        c_float dt, 
        c_float pGain, c_float iGain, c_float dGain
    );
    ~Muscle();

    float* Stretch(c_float &ref);
    float  MeasureForce();
    void   GetGain(float *buff, size_t size) const;
};

#endif //_MUSCLE_
