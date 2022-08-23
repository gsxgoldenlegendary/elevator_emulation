//
// Created by administrator Guo on 2021/10/12 19:08.
//
#include "MyLinkList.h"

MyLinkList::MyLinkList() {
    head = new Student();
    head->next = nullptr;
    tail = head;
}

int MyLinkList::size() {
    auto *p = head->next;
    int n = 0;
    for (; p != nullptr; p = p->next) {
        n++;
    }
    return n;
}

bool MyLinkList::empty() {
    if (head->next == nullptr) {
        return true;
    } else {
        return false;
    }
}

Student MyLinkList::front() {
    if (!empty()) {
        return (Student) (*(head->next));
    }
}

void MyLinkList::push_back(Student& t) {
    auto *student=new Student(t);
    student->next = nullptr;
    tail->next = student;
    tail = tail->next;
}

void MyLinkList::pop_front() {
    Student *temp = head->next;
    if (!empty()) {
        if(tail==head->next){
            tail=head;
        }
        head->next = head->next->next;
        delete temp;
    }
}

Student *MyLinkList::erase(Student *t) {
    for (Student *p = head; p != tail; p = p->next) {
        if (p->next == t) {
            p->next = p->next->next;
            return p->next;
        }
    }
}