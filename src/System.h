//
// Created by administrator Guo on 2021/9/28 17:13.
//

#ifndef DATASTRUCTUREBHW1_SYSTEM_H
#define DATASTRUCTUREBHW1_SYSTEM_H

#include "Elevator.h"
#include "Student.h"
#include "list"

class System {
public:
    bool hasChanged;                    //if the system has changed, it needs outputting.

    System();
    //static may result in bug
    static void Controller(Elevator &); //control elevator
    static void callElevator();         //give elevator station and destination in time
    static void outputState();          //output state of the system
    static void createStudent(int &);   //a student gets into the system
};

#endif //DATASTRUCTUREBHW1_SYSTEM_H