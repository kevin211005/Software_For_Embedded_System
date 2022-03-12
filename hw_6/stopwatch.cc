#include "stopwatch.h"
#include <stdio.h>
#include <chrono>
#include <ratio>

using namespace std::chrono; 
void Stopwatch::start(){
    pre = high_resolution_clock::now();
    _start = true;
    };
void Stopwatch::stop(){
    if (_start){
        nanosec += (high_resolution_clock::now()-pre).count();
    }
    _start = false;
    };
void Stopwatch::reset(){
    nanosec = 0;
    _start = false;
}
double Stopwatch::get_seconds(){
    typedef std::chrono::duration<double,std::ratio<1,1>> sec_type;
    return sec_type(Nano_type(nanosec)).count();
};
double Stopwatch::get_minutes(){
    typedef std::chrono::duration<double,std::ratio<1,1>> sec_type;
    typedef duration<double,std::ratio<60,1>> min_type;
    return min_type(sec_type(Nano_type(nanosec))).count();
};      
double Stopwatch::get_milliseconds()
{
    typedef duration<double,std::milli> milli_type;
    return milli_type(Nano_type(nanosec)).count();
}; 
double Stopwatch::get_nanoseconds(){
    return Nano_type(nanosec).count();
};  


