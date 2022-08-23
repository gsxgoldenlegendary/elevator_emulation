#include "System.h"
#include "Storey.h"
#include "main.h"

int currentTime, occurTime;
Storey storey[5] = {Storey(0), Storey(1), Storey(2), Storey(3), Storey(4)};
System system1;
Elevator elevator1(1);
Elevator elevator2(2);
//it is main function, the main part of the programme
int main() {
    //make CLion output when debugging
    setbuf(stdout, nullptr);
    for (int i = 0; currentTime <= DURATION_TIME; currentTime++) {
        //check whether student giving up at each floor
        for (auto &x: storey) {
            x.checkGiveUp();
        }
        //If it is the time to create another student,then occur one and make one into the system
        if (currentTime == occurTime) {
            System::createStudent(i);
        }
        //refresh state of elevator
        System::callElevator();
        //if it is time for an action to be taken, take action!
        System::Controller(elevator1);
        System::Controller(elevator2);
        //output state of system just when it has changed
        if (system1.hasChanged) {
            System::outputState();
            system1.hasChanged = false;
        }
//System::outputState();
//debugging used
    }
    //it is a good habit
    return 0;
}