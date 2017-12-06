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

/**
 * Singleton class that represents the modeled farm
 */
class Farm : public Event {
public:
    Farm(Farm const&) = delete;
    Farm& operator=(Farm const&) = delete;

    /**
     * Get Farm's instance, create one if it doesn't exist
     * @return shared_ptr of active instance
     */
    static std::shared_ptr<Farm> instance() {
        static std::shared_ptr<Farm> s{new Farm};
        return s;
    }

    /**
     * Initialize Farm with parameters
     * @param _id               farm's assigned ID
     * @param _cows_capacity    Maximum capacity for cows
     * @param _calves_capacity  Maximum capacity for calves
     * @param _cows             Number of cows to start with
     * @param _calves           Number of calves to start with
     * @param _milking_machines Number of milking machines available
     * @param _employees        Number of employees available
     * @param _tank_capacity    Size of milk tank in litres
     */
    void initialize(string _id, int _cows_capacity, int _calves_capacity, int _cows, int _calves, int _milking_machines, int _employees, int _tank_capacity);

    /**
     * Behavior of farm as Event
     */
    void Behavior();

    /**
     * Get farm's ID
     * @return string representing an ID assigned to this farm
     */
    string get_id();

    /**
     * Create and add new calf to herd.
     */
    void new_calf();

    /**
     * Create and add new cow to herd.
     */
    void new_cow();



    shared_ptr<Store> employees;
    shared_ptr<Store> milking_machines;
    shared_ptr<Store> milk_tank;
    shared_ptr<Stall> cows_stall;
    shared_ptr<Stall> calves_stall;

private:
    Farm() {}

    string id;
    int cows_capacity;
    int calves_capacity;
    int cows_cnt;
    int calves_cnt;
    int milking_machines_cnt;
    int employees_cnt;
    int tank_capacity;
    bool initialized = false;

    queue<Cattle*> cows_to_create;
    queue<Cattle*> calves_to_create;

    FarmProcess* process = nullptr;

    string generate_id(int n = 5);
    void generate_calf();
    void generate_cow();
};

/**
 * Helper class to generate timetable-like processes on hourly base
 */
class FarmRoutineGenerator : public Event {
public:
    void Behavior();
};

/**
 * Simulates the occurence of errors of milking machines
 */
class MilkingMachineErrorGenerator : public Event {
public:
    void Behavior();
};

/**
 * Simulates the error of milking machine, including the service period
 */
class MilkingMachineError : public Process {
public:
    void Behavior();
};

/**
 * Milkman process comes once a day and takes all milk from milk tank
 */
class MilkManProcess : public Process {
public:
    void Behavior();
};

#endif
