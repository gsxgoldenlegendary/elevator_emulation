//
// Created by administrator Guo on 2021/9/28 17:13.
//

#include <iostream>
#include "System.h"
#include "main.h"

System::System() {
    hasChanged = false;
}

void System::Controller(Elevator &elevator) {
    //there are several circumstances when the door need opening,
    //it is elevator is going up, going down, or idle & station equal to current floor,
    //& button of current floor in elevator is on, or the direction of elevator is equal to
    //the button which is on in current floor, or elevator has reached destination,
    //or elevator is closing, but a student press button in current floor & it is equal tp
    //the direction of elevator
    if ((currentTime == elevator.actionTime
         && (elevator.state == deceleratingDown
             || elevator.state == deceleratingUp)
         || elevator.state == idle)
        && ((elevator.currentFloor == elevator.station
             && (elevator.callCar[elevator.currentFloor]
                 || elevator.state == deceleratingDown
                    && storey[elevator.currentFloor].callDown
                 || elevator.state == deceleratingUp
                    && storey[elevator.currentFloor].callUp))
            || (elevator.currentFloor == elevator.destination
                && (storey[elevator.currentFloor].callUp
                    || storey[elevator.currentFloor].callDown)))
        || elevator.state == closing
           && elevator.passengers.size() != MAX_CAPACITY
           && (storey[elevator.currentFloor].callUp
               && elevator.destination > elevator.currentFloor
               || storey[elevator.currentFloor].callDown
                  && elevator.destination < elevator.currentFloor)) {
        elevator.openDoor();
    } else if (currentTime == elevator.actionTime
               && (goingUp == elevator.state
                   && elevator.station > elevator.currentFloor
                   || acceleratingUp == elevator.state)) {
        elevator.upOneFloor();
    } else if (currentTime == elevator.actionTime
               && (goingDown == elevator.state
                   && elevator.station < elevator.currentFloor
                   || acceleratingDown == elevator.state)) {
        elevator.downOneFloor();
    } else if (currentTime == elevator.actionTime
               && enterOrLeave == elevator.state) {
        elevator.closeDoor();
    } else if (currentTime == elevator.actionTime
               && opening == elevator.state) {
        elevator.inAndOut();
    } else if (currentTime == elevator.actionTime
               && closing == elevator.state
               || idle == elevator.state
                  && elevator.destination != elevator.currentFloor
               || elevator.state == idle
               || (elevator.state == deceleratingUp
                   && !elevator.callCar[elevator.currentFloor]
                   && !storey[elevator.currentFloor].callDown
                   && !storey[elevator.currentFloor].callUp)) {
        elevator.prepare();
    } else if (currentTime == elevator.actionTime + IDLE_TIME) {
        elevator.waitInFirstFloor();
    } else if (currentTime == elevator.actionTime
               && elevator.passengers.size() != MAX_CAPACITY
               && (goingDown == elevator.state
                   || goingUp == elevator.state)
               && elevator.station == elevator.currentFloor) {
        elevator.startDecelerate();
    }
    //haven't realized waiting in first floor
}

void System::callElevator() {
    elevator1.checkDistance();
    elevator2.checkDistance();
    int minDistance = 100, station_t = elevator1.currentFloor;
    //set station of elevator 1
    if (elevator1.state != acceleratingUp
        && elevator1.state != deceleratingUp
        && elevator1.state != acceleratingDown
        && elevator1.state != deceleratingDown) {
        for (int i = 0; i < 5; i++) {
            if (elevator1.distance[i] < minDistance
                && !(i == elevator1.currentFloor
                     && (elevator1.state == enterOrLeave
                         || elevator1.state == opening
                         || elevator1.state == closing))) {
                minDistance = elevator1.distance[i];
                station_t = i;
            }
        }
        elevator1.station = station_t;
        //set destination of elevator 1
        if (elevator1.station > elevator1.currentFloor
            || elevator1.station == elevator1.currentFloor
               && elevator1.destination > elevator1.currentFloor) {
            for (int i = 4; i >= elevator1.station; i--) {
                if (elevator1.callCar[i]
                    || storey[i].callDown
                    || storey[i].callUp) {
                    elevator1.destination = i;
                    break;
                }
            }
        } else if (elevator1.station < elevator1.currentFloor
                   || elevator1.station == elevator1.currentFloor
                      && elevator1.destination < elevator1.currentFloor) {
            for (int i = 0; i <= elevator1.station; i++) {
                if (elevator1.callCar[i]
                    || storey[i].callDown
                    || storey[i].callUp) {
                    elevator1.destination = i;
                    break;
                }
            }
        }
    }
    //set station of elevator 2
    if (elevator1.state != acceleratingUp
        && elevator1.state != deceleratingUp
        && elevator1.state != acceleratingDown
        && elevator1.state != deceleratingDown) {
        minDistance = 100, station_t = elevator2.currentFloor;
        for (int i = 0; i < 5; i++) {
            if (elevator2.distance[i] < minDistance
                && !(i == elevator2.currentFloor
                     && (elevator2.state == enterOrLeave
                         || elevator2.state == opening
                         || elevator2.state == closing))
                && (elevator2.callCar[i]
                    || elevator1.currentFloor <= elevator1.destination
                       && i != elevator1.destination
                       && (elevator1.currentFloor > i
                           || i > elevator1.destination
                           || storey[i].callDown)
                    || elevator1.currentFloor > elevator1.destination
                       && i != elevator1.destination
                       && (elevator1.currentFloor < i
                           || i < elevator1.destination
                           || storey[i].callUp))) {
                minDistance = elevator2.distance[i];
                station_t = i;
            }
        }
        elevator2.station = station_t;
        //set destination of elevator 2

        if (elevator2.station > elevator2.currentFloor
            || elevator2.station == elevator2.currentFloor
               && elevator2.destination > elevator2.currentFloor) {
            elevator2.destination = 4;
            for (int i = 4; i >= elevator2.station; i--) {
                if (elevator2.callCar[i]
                    || elevator2.station == i
                    || (storey[i].callDown
                        || storey[i].callUp)
                       && (elevator1.currentFloor <= elevator1.destination
                           && i != elevator1.destination
                           && (elevator1.currentFloor > i
                               || i > elevator1.destination
                               || storey[i].callDown)
                           || elevator1.currentFloor > elevator1.destination
                              && i != elevator1.destination
                              && (elevator1.currentFloor < i
                                  || i < elevator1.destination
                                  || storey[i].callUp))) {
                    elevator2.destination = i;
                    break;
                }
            }
        } else if (elevator2.station < elevator2.currentFloor
                   || elevator2.station == elevator2.currentFloor
                      && elevator2.destination < elevator2.currentFloor) {
            elevator2.destination = 0;
            for (int i = 0; i <= elevator2.station; i++) {
                if (elevator2.callCar[i]
                    || elevator2.station == i
                    || (storey[i].callDown
                        || storey[i].callUp)
                       && (elevator1.currentFloor <= elevator1.destination
                           && (elevator1.currentFloor > i
                               || i > elevator1.destination)
                           || elevator1.currentFloor > elevator1.destination
                              && (elevator1.currentFloor < i
                                  || i < elevator1.destination))) {
                    elevator2.destination = i;
                    break;
                }
            }
        }
    }
}

void System::outputState() {
    std::cout << "\tCurrent time:\t" << currentTime
              << "\n\tElevator1:\t"
              << "At floor " << elevator1.currentFloor
              << "\tState:\t" << elevator1.getState() << "\n\t"
              << elevator1.passengers.size() << " student in it."
              << "\tAction time:\t" << elevator1.actionTime
              << "\n\tStation:\t" << elevator1.station
              << "\tDestination:\t" << elevator1.destination
              << "\n\tElevator2:\t"
              << "At floor " << elevator2.currentFloor
              << "\tState:\t" << elevator2.getState() << "\n\t"
              << elevator2.passengers.size() << " student in it."
              << "\tAction time:\t" << elevator2.actionTime
              << "\n\tStation:\t" << elevator2.station
              << "\tDestination:\t" << elevator2.destination;
    for (int i = 0; i < 5; i++) {
        std::cout << "\n\tStorey" << i << ":\t" << storey[i].listUp.size() << " student for up\t"
                  << storey[i].listDown.size() << " student for down";
    }
    //debugging used
//    putchar('\n');
//    for (int i = 0; i < 5; i++) {
//        std::cout << elevator1.distance[i] << " ";
//    }
//    for (int i = 0; i < 5; i++) {
//        std::cout << elevator2.distance[i] << " ";
//    }
    std::cout << "\n\n";
}

void System::createStudent(int &i) {
    Student student(i++);
    occurTime += student.interTime;
    storey[student.inFloor].enQueue(student);
//    Output the new student's information
    std::cout << "\tstudent " << student.number << " appears!\n"
              << "\tFrom:\t" << student.inFloor
              << "\tTo:\t" << student.outFloor
              << "\n\tGive up time:\t" << student.giveUpTime
              << "\tNext student time:" << student.interTime + currentTime << "\n";
}