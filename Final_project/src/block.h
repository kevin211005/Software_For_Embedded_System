#ifndef __BLOCK_AGENT__H
#define __BLOCK_AGENT__H 

#include "enviro.h"

using namespace enviro;
//declare the obstacle behavior 
class BlockController : public Process, public AgentInterface {

    public:
    BlockController() : Process(), AgentInterface() {}

    void init() {
        // initilize the location of obstacle 
        watch("button_click", [&](Event& e) {
            if ( e.value()["value"] == "start_btm" ) {
                teleport( 45, -20, 1.571);
            };
        }); 
        // prevent the item rotation 
        prevent_rotation();
    }
    void start() {}
    void update() {
        //determine the runing range of obstacle 
        if (round(y())<= -20){
            track_velocity(20,0,10,400);
        }
        else if(round(y())>= 145){
            track_velocity(-20,0,10,400);
        } 

    }
    void stop() {}

};
//declare the obstacle agent 
class Block : public Agent {
    public:
    Block(json spec, World& world) : Agent(spec, world) {
        add_process(bc);        
    }
    private:
    BlockController bc;
};

DECLARE_INTERFACE(Block)

#endif