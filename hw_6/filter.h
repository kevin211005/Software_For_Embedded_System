#ifndef FILTER   
#define FILTER
#include "elma/elma.h"
#include <stdio.h>
#include <deque>

using namespace elma;
using namespace std::chrono;
class Filter: public Process {
    public:
    Filter(std::string name) : Process(name){}
    void init();
    void start();
    void update();
    void stop();
    double value();
    private:
    double avg = 0;
    deque<double> container;
};



#endif