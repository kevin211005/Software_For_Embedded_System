#ifndef INTEGRATOR   
#define INTEGRATOR
#include "elma/elma.h"
#include <stdio.h>
#include <deque>

using namespace elma;
using namespace std::chrono;
class Integrator: public Process {
    public:
    Integrator(std::string name) : Process(name){}
    void init();
    void start();
    void update();
    void stop();
    double value();
    private:
    double integal_value;
};



#endif