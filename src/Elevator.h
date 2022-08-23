//
// Created by administrator Guo on 2021/9/28 12:32.
//

#ifndef DATASTRUCTUREBHW1_ELEVATOR_H
#define DATASTRUCTUREBHW1_ELEVATOR_H

#include "MyLinkList.h"
#include "Student.h"
#include "string"

enum ElevatorState {
    goingUp, goingDown, idle, preparing, opening, closing, enterOrLeave,
    acceleratingUp,acceleratingDown,deceleratingUp,deceleratingDown
};
//    bool enterOrLeave;  D1, whether man is entering or leaving elevator
//    bool idle;          D2, whether elevator has stayed for 300t
//    bool vainOpen;      D3, whether elevator door is open & nobody goes through

class Elevator {
public:
    int code;
    int currentFloor;               //current position of thr elevator
    ElevatorState state;            //current state of elevator
    MyLinkList passengers;  //use list to sort students in elevator
    int actionTime;                 //the time when next action of elevator occurs
    int station;                    //the next floor elevator need stop at
    int destination;                //the last floor where elevator end going up or down
    bool callCar[5];
    int distance[5];

    Elevator(int);
    void waitInFirstFloor();    //E1, wait in the first currentFloor

    //realised in controller function in system class
    //void changeState();       E2, determine whether to change the state

    void openDoor();            //E3, open the swing door
    void inAndOut();            //E4, let students get in and out of the elevator1
    void closeDoor();           //E5, shut the swing door
    void prepare();             //E6, prepare for moving
    void upOneFloor();          //E7, go up a currentFloor
    void downOneFloor();        //E8, go down a currentFloor
    void startDecelerate();
    int checkDistance();

    //maybe it isn't needed in this programme
    //void noAction();          E9, make D2 0

    std::string getState() const;
};

#endif //DATASTRUCTUREBHW1_ELEVATOR_H