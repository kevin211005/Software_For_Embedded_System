#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"
#include <stdlib.h>
// // declare the robot behavior
class MyRobotController : public Process, public AgentInterface {

    public:
    MyRobotController() : Process(), AgentInterface(), v(0), omega(0) {}

    void init() {
        // initilize and reset the location of robot 
        watch("button_click", [&](Event& e) {
            if ( e.value()["value"] == "start_btm" ) {
                v = v_m;
                teleport( -445, -175, 0);
            };
        }); 
        //monitoring the keyboards 
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "w" ) {
                //turn left
                omega = -omega_m;              
            } else if ( k == "s" ) {
                //turn right 
                omega = omega_m;  
            }
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            //stop rotate 
            if ( k == "w" || k == "s" ) {
                omega = 0;   
            }            
        });
    }
    void start() { }
    void update() {
        //give the const speed 
        track_velocity(v,omega,10,400);
        //debuging info checking the sensor value 
        //label(std::to_string(sensor_value(0)),0,0);
        //Outside the maze
        if (x() <-460 || y()<-190 ||y()>190){
            teleport( -445, -175, 0);
        }
        // Successfully exist 
        else if (x() >=450){
            std::cout << "You win " << "\n";
            teleport( -445, -175, 0);
        }
        // touching the wall 
        if (sensor_value(0) < 5)
            {
                v = 0;
                teleport( -445, -175, 0);
            }
    }
    void stop() {}

    double v, omega;
    double const v_m = 15, omega_m = 1;
};
//declare the robot agent 
class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MyRobotController c;
};
    

DECLARE_INTERFACE(MyRobot)

#endif