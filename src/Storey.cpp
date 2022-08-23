//
// Created by administrator Guo on 2021/9/28 12:34.
//

#include <iostream>
#include "Storey.h"
#include "main.h"

//Enqueue students into two lists distinguished by up or down
void Storey::enQueue(Student &student) {
    if (student.outFloor > floor) {
        if (elevator1.state == enterOrLeave
            && elevator1.currentFloor == floor
            && elevator1.destination >= elevator1.currentFloor) {
            elevator1.inAndOut();
        } else if (elevator1.state == closing
                   && elevator1.currentFloor == floor
                   && elevator1.destination >= elevator1.currentFloor) {
            elevator1.openDoor();
        } else if (elevator2.state == enterOrLeave
                   && elevator2.currentFloor == floor
                   && elevator2.destination >= elevator2.currentFloor) {
            elevator2.inAndOut();
        } else if (elevator2.state == closing
                   && elevator2.currentFloor == floor
                   && elevator2.destination >= elevator2.currentFloor) {
            elevator2.openDoor();
        } else if (elevator1.state == opening
                   && elevator1.currentFloor == floor
                   && elevator1.destination >= elevator1.currentFloor
                   || elevator2.state == opening
                      && elevator2.currentFloor == floor
                      && elevator2.destination >= elevator2.currentFloor) {
            listUp.push_back(student);
        } else {
            listUp.push_back(student);
            callUp = true;
        }
    } else if (student.outFloor < floor) {
        if (elevator1.state == enterOrLeave
            && elevator1.currentFloor == floor
            && elevator1.destination <= elevator1.currentFloor) {
            elevator1.inAndOut();
        } else if (elevator1.state == closing
                   && elevator1.currentFloor == floor
                   && elevator1.destination <= elevator1.currentFloor) {
            elevator1.openDoor();
        } else if (elevator2.state == enterOrLeave
                   && elevator2.currentFloor == floor
                   && elevator2.destination <= elevator2.currentFloor) {
            elevator2.inAndOut();
        } else if (elevator2.state == closing
                   && elevator2.currentFloor == floor
                   && elevator2.destination <= elevator2.currentFloor) {
            elevator2.openDoor();
        } else if (elevator1.state == opening
                   && elevator1.currentFloor == floor
                   && elevator1.destination <= elevator1.currentFloor
                   || elevator2.state == opening
                      && elevator2.currentFloor == floor
                      && elevator2.destination <= elevator2.currentFloor) {
            listDown.push_back(student);
        } else {
            listDown.push_back(student);
            callDown = true;
        }
    }
}

void Storey::checkGiveUp() {
    for (auto *x = listDown.head->next; x != nullptr;) {
        if (x->giveUpTime == currentTime) {
            std::cout << "\tStudent " << x->number << " gives up at storey " << floor << "\n";
            x = listDown.erase(x);
            system1.hasChanged = true;
        } else {
            x = x->next;
        }
    }
    for (auto *x = listUp.head->next; x != nullptr;) {
        if (x->giveUpTime == currentTime) {
            std::cout << "\tStudent " << x->number << " gives up at storey " << floor << "\n";
            x = listUp.erase(x);
            system1.hasChanged = true;
        } else {
            x = x->next;
        }
    }
}

Storey::Storey(int f) {
    floor = f;
    callDown = false;
    callUp = false;
}