#ifndef RANDOM_PROCESS   
#define RANDOM_PROCESS
#include "elma/elma.h"
#include <stdio.h>

using namespace elma;
using namespace std::chrono;
class RandomProcess: public Process {
    public:
    RandomProcess(std::string name) : Process(name){}
    void init();
    void start();
    void update();
    void stop();
    private:
};



#endif
