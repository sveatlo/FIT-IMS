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

    // string farm_id = "SK1234";
    // int cows_capacity = 1;
    // int cows_init = 0;
    // int calves_capacity = 1;
    // int calves_init = 1;
    // int milking_machines_cnt = 0;
    // int employees_cnt = 0;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    Log::info("Life at a dairy farm - an IMS project experiment");
    SetOutput("dist/model.out");
    RandomSeed(ms);
    Init(0, 10 * YEAR);

    (Farm::instance())->Activate();
    (new FarmRoutineGenerator())->Activate();

    Run();

    return 0;
}
