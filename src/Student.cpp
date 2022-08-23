//
// Created by administrator Guo on 2021/9/28 15:56.
//

#include "Student.h"
#include "random"
#include "main.h"
#include "ctime"

extern "C" { errno_t rand_s(unsigned int *); }

Student::Student(int number) {
    Student::number = number;
    //although a seed is set, it is still not so randomly
    static std::mt19937_64 engine([]() -> unsigned int {
        unsigned int number;
        rand_s(&number);
        return number;
    }());
    std::uniform_real_distribution<double> random(0, 1);
    inFloor = int(random(engine) * 5);
    outFloor = int(random(engine) * 5);
    for (; inFloor == outFloor;) {
        outFloor = int(random(engine) * 5);
    }
    giveUpTime = currentTime + int(random(engine) * 100) + 300;
    interTime = int(random(engine) * 100) + 1;
    system1.hasChanged = true;
    next = nullptr;
}

Student::Student() {
}