//
// Created by administrator Guo on 2021/9/28 15:56.
//

#ifndef DATASTRUCTUREBHW1_STUDENT_H
#define DATASTRUCTUREBHW1_STUDENT_H

class Student {
public:
    int inFloor;        //the floor student gets into elevator
    int outFloor;       //the floor student gets off elevator
    int giveUpTime;     //the time when student give up waiting for elevator
    int interTime;      //the time when next student occurs
    int number;         //the sequence of student
    Student*next;

    Student();
    explicit Student(int);         //M1, enter system, and prepare for next student's appearance
    //realised in storey and elevator class
//    void enterAndWait()const;    M2, press button and wait
//    void queue();                M3, wait in queue
//    void giveUp();               M4, give up
//    void enterElevator();        M5, enter the elevator
//    void leave();                M6, leave
};

#endif //DATASTRUCTUREBHW1_STUDENT_H