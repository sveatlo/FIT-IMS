#ifndef SHARED_H
#define SHARED_H

using namespace std;

// time units
#define MINUTE 1
#define HOUR 60 * MINUTE
#define DAY 24 * HOUR
#define YEAR 365.25f * DAY /// 1 year in seconds

#define SIMULATION_LENGTH 5 * YEAR

// death rates
#define CALVES_DEATH_3DAYS 0.0287
#define CALVES_DEATH_6MONTHS 0.0669
#define CALVES_DEATH_1YEAR 0.0132

#endif
