#ifndef FARM_H
#define FARM_H

#include <memory>
#include <string>
#include <queue>
#include <simlib.h>
#include "log.h"
#include "shared.h"
#include "stall.h"
#include "cattle.h"

using namespace std;

class Stall;
class Cattle;

class Farm : public Event {
public:
    Farm(string id, int _farm_capacity, int _cows, int _calves, int _milking_machines, int _employees);

    void Behavior();
    string get_id();
    void add_cow(string _id);
    void add_calf();
    void remove_calf();
    void remove_cow();

    shared_ptr<Store> employees;
    shared_ptr<Store> milking_machines;
    shared_ptr<Stall> stall;

private:
    string id;
    int farm_capacity;
    int cows_cnt;
    int calves_cnt;
    int cows_desired;
    int calves_desired;
    int milking_machines_cnt;
    int employees_cnt;

    queue<Cattle*> cows_to_create;
    queue<Cattle*> calves_to_create;

    string generate_id(int n = 5);
};

#endif
