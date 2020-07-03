#ifndef LOG
#define LOG

#include <iostream>
#include <sstream>
#include <fstream>

class Log
{
private:
    float* _measuredForce;
    float* _calculatedForce;
    float* _refForce;
    int _size;
public:
    Log(const int size);
    ~Log();

    void Record(int index,const float reff, const float mesf, const float calcf);
    void Save(const char* filepath);
};

#endif//LOG