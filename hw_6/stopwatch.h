#ifndef STOPWATCH
#define STOPWATCH

#include <assert.h>
#include <iostream>
#include <stdio.h>
#include "elma/elma.h"

using namespace std::chrono; 
class Stopwatch{
    public:
        Stopwatch(){};
        void start();              // starts the timer
        void stop();               // stops the timer
        void reset();              // sets stopwatch to zero
        double get_minutes();      // number of minutes counted, as a double
        double get_seconds();      // number of seconds counted, as a double
        double get_milliseconds(); // number of milliseconds counted, as a double
        double get_nanoseconds();  // number of nanoseconds counted, as a double
    private:
        double nanosec = 0;
        bool _start = false;
        high_resolution_clock::time_point pre;
        typedef std::chrono::duration<double,std::nano> Nano_type;
};


#endif