// #ifndef LOG
// #define LOG

// #include <iostream>
// #include <sstream>
// #include <fstream>

// typedef const float c_float;

// class Log
// {
// private:
//     float* _measuredForce;
//     float* _calculatedForce;
//     float* _referencedForce;
//     float* _pidGain;

//     int    _size;
// public:
//     Log(const int size);
//     ~Log();
//     void RecordPidGain(float* gain, size_t size);
//     void Record(int index, c_float force);
//     void Save(const char* filepath);
// };

// #endif//LOG