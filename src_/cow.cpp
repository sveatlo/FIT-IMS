#include "shared.h"
#include "log.h"
#include "cow.h"

Cow::Cow(Farm* farm, string _id) {
    Log::info("Cow was created");

    this->id = _id;
    this->farm = farm;
    this->type = heifer;
    this->sex = female;

    this->cow_routine_generator = new CowDailyRoutineGenerator(this);
}

Cow::~Cow() {
    Log::info("Cow's dead");
    Leave(*this->farm->stall, 1);
    this->farm->remove_cow();

    this->cow_routine_generator->Passivate();
}

void Cow::Behavior() {
    this->cow_routine_generator->Activate();
    Enter(*this->farm->stall, 1);
}
