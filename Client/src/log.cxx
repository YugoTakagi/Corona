#include "../inc/log.hpp"

Log::Log(const int size)
:_size(size)
{
    _refForce = new float[size];
    _measuredForce = new float[size];
    _calculatedForce = new float[size];
}

Log::~Log()
{
    delete[] _measuredForce;
    delete[] _calculatedForce;
}

void Log::Record(int index, const float reff, const float mesf, const float calcf)
{
    _refForce[index] = reff;
    _measuredForce[index] = mesf;
    _calculatedForce[index] = calcf;
}

void Log::Save(const char* filepath)
{
    std::ofstream ofs(filepath);
    ofs << "ref,adj,state" << std::endl;
    for(int i=0; i < _size; ++i)
    {
        ofs << _refForce[i] <<","<< _calculatedForce[i] <<","<< _measuredForce[i] << std::endl;
    }
    ofs.close();
}