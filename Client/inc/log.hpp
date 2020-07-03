#ifndef LOG
#define LOG

#include <iostream>
#include <sstream>
#include <fstream>

typedef const float c_float;

class Log
{
private:
    float* _measuredForce;
    float* _calculatedForce;
    float* _refForce;
    int _size;

    float* _pidGain;
public:
    Log(const int size);
    ~Log();
    void RecordPidGain(c_float pGain, c_float iGain, c_float dGain);
    void Record(int index,c_float reff, c_float mesf, c_float calcf);
    void Save(const char* filepath);
};

#endif//LOG