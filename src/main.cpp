#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/time.h>
#include <simlib.h>
#include "log.h"
#include "shared.h"
#include "farm.h"

void print_help();

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    string farm_id = "SK1234";
    int cows_capacity = 100;
    int cows_init = 1;
    int calves_capacity = 1;
    int calves_init = 0;
    int milking_machines_cnt = 5;
    int employees_cnt = 3;
    int tank_capacity = 20 * 1000;


    int c;
    while (1) {
        static struct option long_options[] = {
            {"help", no_argument, 0, 'h'},
            {"farm-id", required_argument, 0, 'i'},
            {"cows-capacity", required_argument, 0, 'a'},
            {"cows-init", required_argument, 0, 'b'},
            {"calves-capacity", required_argument, 0, 'c'},
            {"calves-init", required_argument, 0, 'd'},
            {"milking-machines", required_argument, 0, 'e'},
            {"employees", required_argument, 0, 'f'},
            {"tank-capacity", required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long(argc, argv, "hi:a:b:c:d:e:f:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
        case 0:
            /* If this option set a flag, do nothing else now. */
            if (long_options[option_index].flag != 0)
                break;
            printf ("option %s", long_options[option_index].name);
            if (optarg)
                printf (" with arg %s", optarg);
            printf ("\n");
            break;

        case 'h':
            print_help();
            return 0;
            break;

        case 'i':
            farm_id = string(optarg);
            break;

        case 'a':
            try {
                cows_capacity = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;

        case 'b':
            try {
                cows_init = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;

        case 'c':
            try {
                calves_capacity = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;

        case 'd':
            try {
                calves_init = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;

        case 'e':
            try {
                milking_machines_cnt = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;

        case 'f':
            try {
                employees_cnt = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;

        case 'g':
            try {
                tank_capacity = stoi(optarg);
            } catch (...) {
                exit(1);
            }
            break;
        }
    }


    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    Log::info("Life at a dairy farm - an IMS project experiment");
    SetOutput("dist/model.out");
    RandomSeed(ms);
    Init(0, 5 * YEAR);

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

void print_help() {
    cout << "farmsim [-h]" << endl;
    cout << "  -h --help\t\tShow this help" << endl;
    cout << "  --farm-id <id>\tID of simulated farm" << endl;
    cout << "  --cows-init\t\tCows to begin the simulation with" << endl;
    cout << "  --cows-capacity\tMaximum number of cows this farm can have" << endl;
    cout << "  --calves-init\t\tNumber of calves to begin the simulation with" << endl;
    // cout << "  --calves-capacity\tf" << endl;
    cout << "  --milking-machines\tNumber of milking machines available" << endl;
    cout << "  --employees\t\tNumber of caretakers to be used" << endl;
    cout << "  --tank-capacity\tCapacity of milk tank" << endl;
}
