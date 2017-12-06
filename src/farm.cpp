#include <iostream>
#include <memory>
#include <algorithm>
#include "farm.h"
#include "cattle_routine.h"

void Farm::initialize(string _id, int _cows_capacity, int _calves_capacity, int _cows, int _calves, int _milking_machines, int _employees, int _tank_capacity) {
    if (this->initialized) {
        return;
    }

    this->id                    = _id;
    this->cows_capacity         = _cows_capacity;
    this->calves_capacity       = _calves_capacity;
    this->cows_cnt              = _cows;
    this->calves_cnt            = _calves;
    this->milking_machines_cnt  = _milking_machines;
    this->employees_cnt         = _employees;
    this->tank_capacity         = _tank_capacity;

    this->employees         = make_shared<Store>("Employees", this->employees_cnt);
    this->milking_machines  = make_shared<Store>("MilkingMachine", this->milking_machines_cnt);
    this->milk_tank         = make_shared<Store>("MilkTank", this->tank_capacity);
    this->cows_stall        = make_shared<Stall>("CowsStall", this->cows_capacity);
    this->calves_stall      = make_shared<Stall>("CalvesStall", this->calves_capacity, true);

    for (int i = 0; i < this->cows_cnt; i++) {
        this->generate_cow();
    }
    for (int i = 0; i < this->calves_cnt; i++) {
        this->generate_calf();
    }

    this->initialized = true;
    this->Activate();
}

void Farm::Behavior() {
    if (this->initialized) {
        while (!this->cows_to_create.empty()) {
            Cattle* to_create = this->cows_to_create.front();
            to_create->Activate();
            this->cows_to_create.pop();
        }

        while (!this->calves_to_create.empty()) {
            Cattle* to_create = this->calves_to_create.front();
            to_create->Activate();
            this->calves_to_create.pop();
        }
    }
}

string Farm::get_id() {
    return this->id;
}

string Farm::generate_id(int n) {
    auto randchar = []() -> char {
        const char charset[] = "0123456789";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(n, 0);
    std::generate_n(str.begin(), n, randchar);

    return str;
}

void Farm::generate_calf() {
    this->calves_to_create.push(new Cattle(this->generate_id(), calf, heifer, Random() < 0.5 ? male : female));
}
void Farm::new_calf() {
    this->generate_calf();
    this->Activate();
}

void Farm::generate_cow() {
    this->cows_to_create.push(new Cattle(this->generate_id(), cow, heifer, female));
}
void Farm::new_cow() {
    this->generate_cow();
    this->Activate();
}

void FarmRoutineGenerator::Behavior() {
    int hour = ((int)Time / HOUR) % 24;

     // feed calfs at 4am, 12pm and 8pm
    if (hour == 4 || hour == 12 || hour == 20) {
        // Log::info("feed calfs at 4am, 12pm and 8pm @ " + to_string(hour));
        for(auto cattle : Farm::instance()->calves_stall->get_cattle()) {
            (new CattleRoutine(cattle.second))->Activate();
        }
    }

    // milk & feed cows at 5am, 5pm
    if (hour == 5 || hour == 17) {
        // Log::info("milk and feed cows at 5am and 5pm");
        for(auto cattle : Farm::instance()->cows_stall->get_cattle()) {
            (new CattleRoutine(cattle.second))->Activate();
        }
    }

    // give milk to creamary
    if (hour == 20) {
        (new MilkManProcess)->Activate();
    }

    if ((int)Time % 525960 == 0) {
        for(auto cattle : Farm::instance()->cows_stall->get_cattle()) {
            cattle.second->age();
        }
    }


    Activate(Time + 1 * HOUR);
}

void MilkingMachineErrorGenerator::Behavior() {
    (new MilkingMachineError)->Activate();
    Activate(Time + Exponential(0.25 * YEAR));
}

void MilkingMachineError::Behavior() {
    Log::error("Milking machine malfunctioned");
    Farm::instance()->milking_machines->Enter(this, 1);
    Wait(Uniform(0.5, 1.5) * DAY);
    Farm::instance()->milking_machines->Leave(1);
}

void MilkManProcess::Behavior() {
    Wait(30 * MINUTE);
    Farm::instance()->milk_tank->Leave(Farm::instance()->milk_tank->Used());
}
