//
// Created by administrator Guo on 2021/9/28 12:34.
//

#ifndef DATASTRUCTUREBHW1_STOREY_H
#define DATASTRUCTUREBHW1_STOREY_H

#include "MyLinkList.h"
#include "Student.h"

class Storey {
public:
    int floor;                      //the floor of the storey
    bool callUp;                    //up button at each storey
    bool callDown;                  //down button at each storey
    MyLinkList listUp;      //list of students going up, realised by list
    MyLinkList listDown;    //list of students going down, realised by list

    explicit Storey(int);
    //make a student in queue including listUp and listDown
    void enQueue(Student &);
    //check whether there is a student who wants to give up
    void checkGiveUp();
};

#endif //DATASTRUCTUREBHW1_STOREY_H