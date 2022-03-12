#include "random_process.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

using namespace elma;
using namespace std::chrono;
void RandomProcess::init(){};
void RandomProcess::start(){};
void RandomProcess::update(){
    double number = (double)rand() / RAND_MAX;
    std::cout << number << " \n";
    channel("link").send(number);
};
void RandomProcess::stop(){};