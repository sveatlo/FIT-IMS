#include <algorithm>
#include "farm.h"

Farm::Farm(string _id, int _farm_capacity, int _cows, int _calves, int _milking_machines, int _employees) {
    this->id = _id;
    this->farm_capacity = _farm_capacity;
    this->cows_cnt = _cows;
    this->calves_cnt = _calves;
    this->milking_machines_cnt = _milking_machines;
    this->employees_cnt = _employees;

    this->employees         = make_shared<Store>("Employees", this->employees_cnt);
    this->milking_machines  = make_shared<Store>("MilkingMachine", this->milking_machines_cnt);
    this->stall             = make_shared<Stall>(this->farm_capacity);


    for (int i = 0; i < this->cows_cnt; i++) {
        this->cows_to_create.push(new Cattle(this, this->generate_id(), heifer, female));
    }
    for (int i = 0; i < this->calves_cnt; i++) {
        this->calves_to_create.push(new Cattle(this, this->generate_id(), calf, Random() < 0.5 ? male : female));
    }
}

void Farm::Behavior() {
    Log::debug("farm behavior");
    while (!this->cows_to_create.empty()) {
        Log::debug("poping cow");
        Cattle* to_create = this->cows_to_create.front();
        to_create->Activate();
        this->cows_to_create.pop();
    }

    while (!this->calves_to_create.empty()) {
        Log::debug("poping calf");
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
