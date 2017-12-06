#ifndef FARM_H
#define FARM_H

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include <simlib.h>
#include "log.h"
#include "shared.h"
#include "cattle.h"
#include "stall.h"

using namespace std;

// forward declarations
class Cattle;
class FarmProcess;
class Stall;

class Farm : public Event {
public:
    Farm(Farm const&) = delete;
    Farm& operator=(Farm const&) = delete;

    static std::shared_ptr<Farm> instance() {
        static std::shared_ptr<Farm> s{new Farm};
        return s;
    }

    void Behavior();
    string get_id();
    void new_calf();
    void new_cow();

    shared_ptr<Store> employees;
    shared_ptr<Store> milking_machines;
    shared_ptr<Stall> cows_stall;
    shared_ptr<Stall> calves_stall;

private:
    Farm() : Farm("SK1234", 100, 25, 1, 1, 1, 1, 1000) {}
    Farm(string _id, int _cows_capacity, int _calves_capacity, int _cows, int _calves, int _milking_machines, int _employees, int _tank_capacity);

    string id;
    int cows_capacity;
    int calves_capacity;
    int cows_cnt;
    int calves_cnt;
    int milking_machines_cnt;
    int employees_cnt;
    int tank_capacity;
    bool just_initialized = true;

    queue<Cattle*> cows_to_create;
    queue<Cattle*> calves_to_create;

    FarmProcess* process = nullptr;

    string generate_id(int n = 5);
};

class FarmRoutineGenerator : public Event {
public:
    void Behavior();

private:
    Farm* farm;
};

#endif
