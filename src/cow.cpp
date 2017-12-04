#include "shared.h"
#include "log.h"
#include "cow.h"

Cow::Cow() {
    Log::info("Cow was created");
    this->type = heifer;
    this->sex = female;

    // go to CowsStall
    Enter(CowsStall, 1);

    this->cow_routine_generator = new CowDailyRoutineGenerator(this);
}

Cow::~Cow() {
    Log::info("Cows dead");
    Leave(CowsStall, 1);
}

void Cow::Behavior() {
    this->cow_routine_generator->Activate();
}


CowDailyRoutineGenerator::CowDailyRoutineGenerator(Cow* _cow) {
    this->cow = _cow;
}

void CowDailyRoutineGenerator::Behavior() {
    (new CowDailyRoutine(this->cow))->Activate();
    Activate(Time + 12 * HOUR);
}

CowDailyRoutine::CowDailyRoutine(Cow* _cow) {
    this->cow = _cow;
}

void CowDailyRoutine::Behavior() {
    switch (this->cow->state) {
        case NotMilked:
            break;

        case Milked:
            break;

        case AfterCalving:
            break;
    }
}
