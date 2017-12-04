#ifndef SHARED_H
#define SHARED_H

#include <simlib.h>

#define HOUR 60
#define DAY 24 * HOUR
#define YEAR 365.25f * DAY /// 1 year in seconds

// shared stores
extern Store CalfCareTakers;
extern Store CowsStall;
extern Store MilkingMachines;

#endif
