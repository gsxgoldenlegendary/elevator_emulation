//
// Created by administrator Guo on 2021/9/28 21:45.
//

#ifndef DATASTRUCTUREBHW1_MAIN_H
#define DATASTRUCTUREBHW1_MAIN_H

#include "System.h"
#include "Storey.h"
#include "Elevator.h"

typedef int Time;

extern Storey storey[5];                        //definition of 5 storeys
extern System system1;                          //definition of the event system
extern Elevator elevator1;                      //definition of elevator 1
extern Elevator elevator2;                      //definition of elevator 1
extern Time currentTime,occurTime;               //global time & current time

constexpr int MAX_CAPACITY(10);                 //max capacity of an elevator
constexpr int UP_TIME(51);                      //time of going up a floor
constexpr int DOWN_TIME(61);                    //time of going down a floor
constexpr int CLOSE_TIME(20);                   //time of closing door
constexpr int OPEN_TIME(20);                    //time of opening door
constexpr int ENTER_OR_LEAVE_TIME(20);          //time of the first time door open
constexpr int DURATION_TIME(1000);              //time of all the events
constexpr int IDLE_TIME(300);                   //if elevator isn't used for such time, it'll be set idle
constexpr int UP_ACCELERATE_TIME(15);           //time of elevator accelerate up
constexpr int DOWN_ACCELERATE_TIME(15);         //time of elevator accelerate down
constexpr int UP_DECELERATE_TIME(14);           //time of elevator decelerate up
constexpr int DOWN_DECELERATE_TIME(23);         //time of elevator decelerate down
#endif //DATASTRUCTUREBHW1_MAIN_H