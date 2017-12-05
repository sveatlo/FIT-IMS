#include "shared.h"
#include "calf_routine.h"

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
    Enter(*this->calf->farm->employees, 1); // seize 1 caretaker for feeding
    Wait(Time + Uniform(1, 3)); // it takes 1-3 minutes to start feeding the calf
    Leave(*this->calf->farm->employees, 1); // the calf can eat now

    Wait(Time + 30); // calfs are given 30 minutes for eating

    Enter(*this->calf->farm->employees, 1); // seize 1 caretaker for cleanup
    Wait(Time + Uniform(0, 1)); // it takes 1 or less to clean up after eating
    Leave(*this->calf->farm->employees, 1); // the calf can eat now
}
