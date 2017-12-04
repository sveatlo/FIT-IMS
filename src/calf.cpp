#include <iostream>
#include "shared.h"
#include "log.h"
#include "calf.h"

Calf::Calf(Sex _sex) {
    Log::info("new calf created");

    this->type = calf;
    this->sex = _sex;
    this->daily_routine_generator = new CalfRoutineGenerator(this);

}

void Calf::Behavior() {
    this->daily_routine_generator->Activate();

    Log::info("Calf was born");
    Wait(2 * YEAR);
    this->daily_routine_generator->Passivate();

    if (this->sex == male) {
        Log::info("Calf is now a grown-up bull => send to the butcher's house");
        this->Terminate();
    } else {
        Log::info("Calf is now a grown-up heifer => add to stall if possible, sell otherwise");
        if(CowsStall.Full()) {
            this->Terminate();
        } else {
            // create cow
        }
    }
}

CalfRoutineGenerator::CalfRoutineGenerator(Calf* _calf) {
    this->calf = _calf;
}

void CalfRoutineGenerator::Behavior() {
    (new CalfRoutine(this->calf))->Activate();
    Activate(Time + 8 * HOUR);
}

CalfRoutine::CalfRoutine(Calf* _calf) {
    this->calf = _calf;
}

void CalfRoutine::Behavior() {
    Enter(CalfCareTakers, 1); // seize 1 caretaker for feeding
    Wait(Time + Uniform(1, 3)); // it takes 1-3 minutes to start feeding the calf
    Leave(CalfCareTakers, 1); // the calf can eat now

    Wait(Time + 30); // calfs are given 30 minutes for eating

    Enter(CalfCareTakers, 1); // seize 1 caretaker for cleanup
    Wait(Time + Uniform(0, 1)); // it takes 1 or less to clean up after eating
    Leave(CalfCareTakers, 1); // the calf can eat now
}
