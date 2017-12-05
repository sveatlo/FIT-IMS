#ifndef FARM_H
#define FARM_H

#include <memory>
#include <simlib.h>
#include "log.h"
#include "shared.h"
#include "calf.h"
#include "cow.h"

using namespace std;

class Farm : public Event {
friend class Cattle;
friend class Calf;
friend class CalfRoutine;

public:
    Farm(int _farm_capacity, int _cows, int _calves, int _milking_machines, int _employees);

    void Behavior();

private:
    int farm_capacity;
    int cows_cnt;
    int calves_cnt;
    int milking_machines_cnt;
    int employees_cnt;

    shared_ptr<Store> employees;
    shared_ptr<Store> milking_machines;
    // shared_ptr<CowsStall> stall;
};

#endif
