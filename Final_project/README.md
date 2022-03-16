# Final Project
## The goal 
The main goal of this project is to build the simple maze like video game. The player control the robot to escape the maze. 
![image](https://user-images.githubusercontent.com/86145579/158491329-3155698a-b039-412f-8925-cbbf9c386dd6.png)

## Installation 
- Install the docker 
- Run the docker Image, and change the ``` $PWD ``` to your local path of this project
```bash
docker run -p80:80 -p8765:8765 -v  $PWD:/source -it klavins/enviro:v1.5 bash
```
- The next step: start ENVIRO run
```bash
esm start 
```
- All environment is setted now.
- Construct this project by 
```bash
Make
```
- Run this project to local server
```
enviro
```
- Using web browser http://localhost to see the ENVIRO client

## Challenge 
For this projects, there are three main challenges. 
1. Create the maze. 

    i.  Figure out how to write the json file.
    
    ii. Understand each elements meaning in the config.json.
    
    In order to create the maze, basic knowlegde of json and project config is needed. 
    
    Here is the reference of those inforamtion.
    
    https://github.com/klavinslab/enviro
  
    https://github.com/tbonaciUW/EEP_520_Winter2022/blob/main/week8/Lecture8_README.md
    
2. Control the robot

    i.  Watch Keyboard event
    
    Using watch command to detect the keyboards action by 
    
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            //do something
            });
    
    ii. Set the reasonable initial speed of robot
    
    Manually fine-tune the initial speed of robot and set the speed to robot by 
        
        void track_velocity(double linear_velocity, double angular_velocity, double kL=10, double kR=10)
    
3. Monitor collison 

    i. Detect the collison between agent and static elements 
    
    ii. Monitor the collison between agent and agent 
    
    To detect the collision ```void notice_collisions_with(const std::string agent_type, std::function<void(Event&)> handler)``` is used to detect the collision, but it only
        detect the collision between agent and agent, so putting sensor to detect the wall is needed and do it by
        """bash
        
        "sensor": [
        {
           "type": "range",
           "location": { "x": 12, "y": 0 },
           "direction": 0
        }
        ]
        
        """
    
    iii. Return the start point 
## Introduction 
Background story

There is the people who was be imprisoned, and his head is be implanted the chip that will be detected from the wall if this chip is too close the wall. Thus, if this person want to escape from the jail, he has to stay away from the wall, and the chip will sent the location inforamtion regularly, so he can't stop if he decide to escape. 

For this game,

Press start button to start the game!

Only two ways to control this people,

-Press ```w``` in keyboards to turn left 

-Press ```s``` in keyborads to turn right 

-During the game, let people's head away from the wall and regularly scaning sensor 

-If be detected, it will return to the start point.

-If passed the maze, ![image](https://user-images.githubusercontent.com/86145579/158494744-a1f1c557-17b4-4c86-bf22-15a5ef0dbf94.png)
it will shows in your terminal 
## Reference 
This project is based on enviro backend. 
Here is the link for more information https://github.com/klavinslab/enviro
