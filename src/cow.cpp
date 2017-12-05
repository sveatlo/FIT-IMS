#include "shared.h"
#include "log.h"
#include "cow.h"

Cow::Cow(Farm* farm) {
    Log::info("Cow was created");

    this->farm = farm;
    this->type = heifer;
    this->sex = female;

    // go to CowsStall
    // Enter(*Shared::instance()->stall, 1);

    this->cow_routine_generator = new CowDailyRoutineGenerator(this);
}

Cow::~Cow() {
    Log::info("Cow's dead");
    // Leave(*Shared::instance()->stall, 1);
}

void Cow::Behavior() {
    this->cow_routine_generator->Activate();
    Log::debug("cow is doing somehitng for 28 days");

    Activate(Time + 28 * DAY);

    this->cow_routine_generator->Passivate();
}
