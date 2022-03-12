#include "filter.h"
#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

using namespace elma;
using namespace std::chrono;
void Filter::init(){
    avg = 0;
};
void Filter::start(){};
void Filter::update(){
    if (channel("link").nonempty()){
        if (container.size() >= 10){
            container.pop_front();
        }
        container.push_back(channel("link").latest());
    }
};
double Filter::value(){
    if (container.size() == 0){return avg;}
    double sum = 0;
    
    for (int i; i < container.size();i++ ){
        //std::cout << container.at(i) << " \n";
        sum += container.at(i);
    }
    //std::cout << "Sum-------------------------" << " \n";
    return (double) sum/container.size();
};
void Filter::stop(){};