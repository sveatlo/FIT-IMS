#include <iostream>
#include "shared.h"
#include "log.h"
#include "calf.h"

Calf::Calf(Farm* _farm) {
    this->farm = _farm;
    this->type = calf;
    if (Random() < 0.5) {
        this->sex = male;
    } else {
        this->sex = female;
    }

    this->daily_routine_generator = new CalfRoutineGenerator(this);
}

Calf::~Calf() {
    Log::info("Calf's gone");
    this->farm->remove_calf();
}

void Calf::Behavior() {
    Log::info("Calf was born - " + this->id);
    this->daily_routine_generator->Activate();

    if (this->sex == male) {
        // young bulls are kept for 1 years, they are sold afterwards
        Wait(1 * YEAR);
    } else {
        // young heifers are kept as calves until their first rut
        // this usually happens around 21st month for most heifers
        Wait(Normal(1.75, 0.25) * YEAR);
    }
    this->daily_routine_generator->Passivate();

    if (this->sex == male) {
        this->Terminate();
    } else {
        if(!this->farm->stall->Full()) {
            this->farm->calf_to_cow(this->id);
        }
        // Sell it
        this->Terminate();
    }
}
