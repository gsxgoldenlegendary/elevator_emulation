//
// Created by administrator Guo on 2021/9/28 12:32.
//

#include <iostream>
#include "Elevator.h"
#include "main.h"

Elevator::Elevator(int i) {
    code = i;
    currentFloor = 1;           //when the programme starts, elevator is at floor 1
    state = idle;
    actionTime = 0;
    station = 1;
    destination = 1;
    for (auto i: callCar) {
        callCar[i] = false;
    }
    for (auto i: distance) {
        distance[i] = 100;      //100 means needn't reach
    }
}

void Elevator::waitInFirstFloor() {
    destination = 1;
    station = 1;
}

void Elevator::inAndOut() {
    state = enterOrLeave;
    //Students get off the elevator.
    for (auto *iter = passengers.head->next; iter != nullptr;) {
        if (iter->outFloor == currentFloor) {
            std::cout << "\tStudent " << iter->number << " gets off elevator " << code << " .\n";
            iter = passengers.erase(iter);
        } else {
            iter = iter->next;
        }
    }
    //Students get into the elevator
    if (!storey[currentFloor].callDown) {
        for (; !storey[currentFloor].listDown.empty()
               && passengers.size() != MAX_CAPACITY;) {
            Student s = storey[currentFloor].listDown.front();
            std::cout << "\tStudent " << s.number << " gets into elevator " << code << " .\n";
            passengers.push_back(s);
            callCar[s.outFloor] = true;
            storey[currentFloor].listDown.pop_front();
        }
    }
    if (!storey[currentFloor].callUp) {
        for (; !storey[currentFloor].listUp.empty()
               && passengers.size() != MAX_CAPACITY;) {
            Student s = storey[currentFloor].listUp.front();
            std::cout << "\tStudent " << s.number << " gets into elevator " << code << " .\n";
            passengers.push_back(s);
            callCar[s.outFloor] = true;
            storey[currentFloor].listUp.pop_front();
        }
    }
    actionTime = currentTime + ENTER_OR_LEAVE_TIME;
    system1.hasChanged = true;
}

void Elevator::openDoor() {
    //if elevator will go up, callUP canceled in current floor
    //it occurs when elevator is going up, or idle, or it has reached destination of going down
    if ((state == deceleratingUp
         || state == idle
         || state == deceleratingDown
            && destination == currentFloor)
        && storey[currentFloor].callUp) {
        storey[currentFloor].callUp = false;
    }
        //if elevator will go down, callDOWN canceled in current floor
        //it occurs when elevator is going down, or it has reached destination of going up
    else if ((state == deceleratingDown
              || state == idle
              || state == deceleratingUp
                 && destination == currentFloor)
             && storey[currentFloor].callDown) {
        storey[currentFloor].callDown = false;
    }
    //cancel the button of current floor
    callCar[currentFloor] = false;
    state = opening;
    actionTime = currentTime + OPEN_TIME;
    system1.hasChanged = true;
}

void Elevator::closeDoor() {
    state = closing;
    actionTime = currentTime + CLOSE_TIME;
    system1.hasChanged = true;
}

std::string Elevator::getState() const {
    switch (state) {
        case goingUp:
            return "GOING UP";
        case goingDown:
            return "GOING DOWN";
        case idle:
            return "IDLE";
        case preparing:
            return "PREPARING";
        case opening:
            return "OPENING";
        case closing:
            return "CLOSING";
        case enterOrLeave:
            return "ENTER OR LEAVE";
        case acceleratingUp:
            return "ACCELERATING UP";
        case acceleratingDown:
            return "ACCELERATING DOWN";
        case deceleratingUp:
            return "DECELERATING UP";
        case deceleratingDown:
            return "DECELERATING DOWN";
    }
}

void Elevator::upOneFloor() {
    currentFloor++;
    actionTime += UP_TIME;
    state = goingUp;
    system1.hasChanged = true;
}

void Elevator::downOneFloor() {
    currentFloor--;
    actionTime += DOWN_TIME;
    state = goingDown;
    system1.hasChanged = true;
}

void Elevator::prepare() {
    if (destination > currentFloor) {
        state = acceleratingUp;
        actionTime = currentTime + UP_ACCELERATE_TIME;
        system1.hasChanged = true;
    } else if (destination < currentFloor) {
        state = acceleratingDown;
        actionTime = currentTime + DOWN_ACCELERATE_TIME;
        system1.hasChanged = true;
    } else {
        state = idle;
        destination = currentFloor;
        station = currentFloor;
    }
}

void Elevator::startDecelerate() {
    if (state == goingUp) {
        state = deceleratingUp;
        actionTime = currentTime + UP_DECELERATE_TIME;
    } else if (state == goingDown) {
        state = deceleratingDown;
        actionTime = currentTime + DOWN_DECELERATE_TIME;
    }
    system1.hasChanged = true;
}

int Elevator::checkDistance() {
    for (int i = 0; i < 5; i++) {
        int distance1 = 100, distance2 = 100, distance3 = 100;
        //check callCar
        if (callCar[i]) {
            distance1 = abs(i - currentFloor);
        }
        //check callUp
        if (storey[i].callUp) {
            if (destination >= currentFloor) {
                if (i >= currentFloor) {
                    distance2 = i - currentFloor;
                } else {
                    distance2 = destination - i + destination - currentFloor;
                }
            } else {
                if (i < destination) {
                    distance2 = currentFloor - i;
                } else {
                    distance2 = i - destination + currentFloor - destination;
                }
            }
        }
        //check callDown
        if (storey[i].callDown) {
            if (destination >= currentFloor) {
                if (destination >= i) {
                    distance3 = destination - i + destination - currentFloor;
                } else {
                    distance3 = i - currentFloor;
                }
            } else {
                if (i > currentFloor) {
                    distance3 = i - destination + currentFloor - destination;
                } else {
                    distance3 = currentFloor - i;
                }
            }
        }
        distance[i] = std::min(std::min(distance1, distance2), distance3);
    }
}