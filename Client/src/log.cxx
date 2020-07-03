#include "../inc/log.hpp"

Log::Log(const int size)
:_size(size)
{
    _refForce = new float[size];
    _measuredForce = new float[size];
    _calculatedForce = new float[size];

    _pidGain = new float[3];
}

Log::~Log()
{
    delete[] _refForce;
    delete[] _measuredForce;
    delete[] _calculatedForce;

    delete[] _pidGain;
}

void Log::RecordPidGain(c_float pGain, c_float iGain, c_float dGain)
{
    _pidGain[0] = pGain;
    _pidGain[1] = iGain;
    _pidGain[2] = dGain;
}

void Log::Record(int index, c_float force[3])
{
    _refForce[index] = force[0];
    _measuredForce[index] = force[1];
    _calculatedForce[index] = force[2];
}

void Log::Save(const char* filepath)
{
    std::ofstream ofs(filepath);
    ofs << "pGain," << _pidGain[0] << std::endl;
    ofs << "iGain," << _pidGain[1] << std::endl;
    ofs << "dGain," << _pidGain[2] << std::endl;
    ofs << "ref,adj,state" << std::endl;
    for(int i=0; i < _size; ++i)
    {
        ofs << _refForce[i] <<","<< _calculatedForce[i] <<","<< _measuredForce[i] << std::endl;
    }
    ofs.close();
}