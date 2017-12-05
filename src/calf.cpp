#include <iostream>
#include "shared.h"
#include "log.h"
#include "calf.h"

Calf::Calf(Farm* _farm, Sex _sex) {
    Log::info("new calf created");

    this->farm = _farm;
    this->type = calf;
    this->sex = _sex;
    this->daily_routine_generator = new CalfRoutineGenerator(this);
}

Calf::~Calf() {
    Log::info("Calf's gone");
}

void Calf::Behavior() {
    this->daily_routine_generator->Activate();

    Log::info("Calf was born");
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
        Log::info("Calf is now a grown-up bull => send to the butcher's house");
        this->Terminate();
    } else {
        Log::info("Calf is now a grown-up heifer => add to stall if possible, sell otherwise");
        // if(!Shared::instance()->stall->Full()) {
        //     // create cow
        //     Shared::instance()->stall->new_cow();
        // }
        // Sell it
        this->Terminate();
    }
}
