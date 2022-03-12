#include "integrator.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

using namespace elma;
using namespace std::chrono;
void Integrator::init(){
    integal_value = 0;
};
void Integrator::start(){};
void Integrator::update(){
     integal_value += (double) channel("link").latest();
};
double Integrator::value(){
    return (double) integal_value;
};
void Integrator::stop(){};