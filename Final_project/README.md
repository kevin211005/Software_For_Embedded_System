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
## Introduction 
## Reference 
