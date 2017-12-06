#include <iostream>
#include <sys/time.h>
#include <simlib.h>
#include "log.h"
#include "shared.h"
#include "farm.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
	srand(time(NULL));

    string farm_id = "SK1234";
    int cows_capacity = 300;
    int cows_init = 100;
    int calves_capacity = 25;
    int calves_init = 0;
    int milking_machines_cnt = 5;
    int employees_cnt = 2;
    int tank_capacity = 50 * 1000;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    Log::info("Life at a dairy farm - an IMS project experiment");
    SetOutput("dist/model.out");
    RandomSeed(ms);
    Init(0, SIMULATION_LENGTH);

    Farm::instance()->initialize(farm_id, cows_capacity, calves_capacity, cows_init, calves_init, milking_machines_cnt, employees_cnt, tank_capacity);
    Farm::instance()->Activate();
    (new FarmRoutineGenerator())->Activate();

    Run();

    for(auto cattle : Farm::instance()->cows_stall->get_cattle()) {
        cattle.second->get_statistics()->output();
    }

    Farm::instance()->cows_stall->Output();
    Farm::instance()->calves_stall->Output();
    Farm::instance()->employees->Output();
    Farm::instance()->milking_machines->Output();
    Farm::instance()->milk_tank->Output();

    return 0;
}
