#include <iostream>
#include <memory>
#include <algorithm>
#include "farm.h"
#include "cattle_routine.h"

Farm::Farm(string _id, int _cows_capacity, int _calves_capacity, int _cows, int _calves, int _milking_machines, int _employees, int _tank_capacity) {
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
    this->cows_stall        = make_shared<Stall>(this->cows_capacity);
    this->calves_stall      = make_shared<Stall>(this->calves_capacity);
}

void Farm::Behavior() {
    if(this->just_initialized) {
        for (int i = 0; i < this->cows_cnt; i++) {
            this->new_cow();
        }
        for (int i = 0; i < this->calves_cnt; i++) {
            this->new_calf();
        }
    }

    this->just_initialized = false;
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

void Farm::new_calf() {
    this->calves_to_create.push(new Cattle(this->generate_id(), calf, heifer, Random() < 0.5 ? male : female));
    this->Activate();
}

void Farm::new_cow() {
    this->cows_to_create.push(new Cattle(this->generate_id(), cow, heifer, female));
    this->Activate();
}

void FarmRoutineGenerator::Behavior() {
    if ((((((int)Time / HOUR) % 8) - 4) == 0)) { // feed calfs at 4am, 12pm and 8pm
        // Log::info("feed calfs at 4am, 12pm and 8pm");
        for(auto cattle : Farm::instance()->calves_stall->get_cattle()) {
            (new CattleRoutine(cattle.second))->Activate();
        }
    }

    if ((((((int)Time / HOUR) % 12) - 5) == 0)) { // feed calfs at 4am, 12pm and 8pm
        // Log::info("milk and feed cows at 5am and 5pm");
        for(auto cattle : Farm::instance()->cows_stall->get_cattle()) {
            (new CattleRoutine(cattle.second))->Activate();
        }
    }


    Activate(Time + 1 * HOUR);
}
