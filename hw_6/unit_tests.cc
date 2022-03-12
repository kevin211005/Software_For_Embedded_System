#include <math.h>
#include <fstream>
#include <assert.h>
#include "gtest/gtest.h"
#include "stopwatch.h"
#include "integrator.h"
#include "random_process.h"
#include "filter.h"
#include "elma/elma.h"

namespace {
    using namespace std::chrono; 
    using namespace elma;   
    void waste_time() {
        std::this_thread::sleep_for(1_s);
    }
    TEST(dsf,watch) {
        Stopwatch w;
        w.start();
        waste_time();
        w.stop();   
        w.stop(); 
        w.start();
        waste_time();
        w.stop();  
        ASSERT_GE(w.get_seconds(),2); 
        ASSERT_GE(w.get_milliseconds(),2000); 
        ASSERT_GE(w.get_minutes(),double (2.0/60)); 
        w.reset();
        ASSERT_GE(w.get_minutes(),0); 
        w.stop(); 
        ASSERT_GE(w.get_minutes(),0); 
        w.start();
        waste_time();
        w.stop();   
        ASSERT_GE(w.get_seconds(),1); 
    }    
    TEST(random,random_filter){
        Manager m;
        RandomProcess r("random numbers");
        Filter f("filter");
        elma::Channel link("link");

        m.schedule(r, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(10_ms);
    }
    class NumberProcess: public Process {
        public:
        NumberProcess(std::string name) : Process(name){}
        void init(){
            pre_value = 0.75;
        };
        void start(){};
        void update(){
            if (pre_value == 0.75){
                pre_value = 0.25;
            }
            else{
                pre_value = 0.75;
            }
            channel("link").send(pre_value);
        };
        void stop(){};
        private:
        double pre_value;
    };
    TEST(filter,random_filter){
        Manager m;
        NumberProcess n("random numbers");
        Filter f("filter");
        elma::Channel link("link");
        EXPECT_DOUBLE_EQ(f.value(),0.0);
        m.schedule(n, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(101_ms);
        EXPECT_DOUBLE_EQ(f.value(),0.5);
    }
    TEST(five_round,random_filter){
        Manager m;
        NumberProcess n("random numbers");
        Filter f("filter");
        elma::Channel link("link");
        m.schedule(n, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(5_ms);
        EXPECT_DOUBLE_EQ(f.value(),0.5);
    }
    class IntProcess: public Process {
        public:
        IntProcess(std::string name) : Process(name){}
        void init(){
            pre_value = 1;
        };
        void start(){};
        void update(){
            pre_value = 1;
            channel("link").send(pre_value);
        };
        void stop(){};
        private:
        double pre_value;
    };
    TEST(intergral,integrator){
        Manager m;
        IntProcess n("same number");
        Integrator integrator("integrator");
        elma::Channel link("link");
        m.schedule(n, 1_ms)
        .schedule(integrator, 1_ms)
        .add_channel(link)
        .init()
        .run(5_ms);
        EXPECT_DOUBLE_EQ(integrator.value(),4);
    }
}