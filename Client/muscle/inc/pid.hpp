#ifndef _PIDCONTROLER_
#define _PIDCONTROLER_

#include <iostream>

typedef const float c_float;

class PidControler
{
private:
    c_float _pGain;
    c_float _iGain;
    c_float _dGain;

    c_float _dt;

    float   _adjustment;
    float   _diff[2];
    float   _integral;
public:
    PidControler
    (
        c_float dt, 
        c_float pGain, c_float iGain, c_float dGain
    );
    ~PidControler(void);

    float run(c_float ref, c_float state);
};

#endif //_PIDCONTROLER_
