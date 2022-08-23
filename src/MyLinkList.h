//
// Created by administrator Guo on 2021/10/11 09:08.
//

#ifndef DATASTRUCTUREBHW1_MYLINKLIST_H
#define DATASTRUCTUREBHW1_MYLINKLIST_H

#include "Student.h"

using namespace std;

class MyLinkList {
public:
    Student *head;
    Student *tail;

    MyLinkList();
    int size();
    void pop_front();
    void push_back(Student &);
    Student *erase(Student *);
    Student front();
    bool empty();
};

#endif //DATASTRUCTUREBHW1_MYLINKLIST_H