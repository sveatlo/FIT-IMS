#include "farm.h"

Farm::Farm(int _farm_capacity, int _cows, int _calves, int _milking_machines, int _employees) {
    this->farm_capacity = _farm_capacity;
    this->cows_cnt = _cows;
    this->calves_cnt = _calves;
    this->milking_machines_cnt = _milking_machines;
    this->employees_cnt = _employees;

    this->employees         = make_shared<Store>("Employees", this->employees_cnt);
    this->milking_machines  = make_shared<Store>("MilkingMachine", this->milking_machines_cnt);
    // this->stall             = make_shared<CowsStall>(this->farm_capacity);
}

void Farm::Behavior() {
    for (int i = 0; i < this->cows_cnt; i++) {
        (new Cow(this))->Activate();
    }

    for (int i = 0; i < this->calves_cnt; i++) {
        (new Calf(this, female))->Activate();
    }
}
