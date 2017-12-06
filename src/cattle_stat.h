#ifndef COW_STATISTICS_H
#define COW_STATISTICS_H

#include <map>
#include <simlib.h>
#include <string>
#include "shared.h"
#include "cattle.h"

using namespace std;

class Cattle;
class Lactation;

class CattleStat {
public:
    CattleStat(Cattle* _cattle);

    void output();
    void die(double time);
    void milk(double milk);

private:
    Cattle* cattle;

    map<int, Lactation*> lactation_stats;
    Histogram* lifetime_milk;

    double died_at;
};

class Lactation {
public:
    void milk(int day, double milking_amount);
    void csv_output();
    void statistics_output();

private:
    map<int, double> histogram;

    double total = 0;
    double min = SIMULATION_LENGTH;
    double max = 0;
    double average;
    double first_record = -1;
    double last_record = 0;
};

#endif
