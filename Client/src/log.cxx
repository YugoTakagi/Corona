#include "../inc/log.hpp"

Log::Log(const int size)
: _size(size)
{
    _referencedForce = new float[_size];
    _measuredForce   = new float[_size];
    _calculatedForce = new float[_size];

    _pidGain = new float[3];
}

Log::~Log()
{
    delete[] _referencedForce;
    delete[] _measuredForce;
    delete[] _calculatedForce;

    delete[] _pidGain;
}

void Log::RecordPidGain(float* gain, size_t size)
{
    if((size/sizeof(float)) != 3) exit(1);
    _pidGain[0] = gain[0];
    _pidGain[1] = gain[1];
    _pidGain[2] = gain[2];
}

void Log::Record(int index, c_float force[3])
{
    _referencedForce[index] = force[0];
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
        ofs << _referencedForce[i] <<","<< _calculatedForce[i] <<","<< _measuredForce[i] << std::endl;
    }
    ofs.close();
    std::cout << ">>> log file as \"" << filepath << "\"." << std::endl;
}