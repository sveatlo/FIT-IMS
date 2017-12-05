#include "shared.h"
#include "cow_routine.h"


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
