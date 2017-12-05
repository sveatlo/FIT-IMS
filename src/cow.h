#ifndef COW_H
#define COW_H

#include <simlib.h>
#include "farm.h"
#include "cattle.h"
#include "cow_routine.h"

class Farm;
class CowDailyRoutineGenerator;
class CowDailyRoutine;


typedef enum {
    NotMilked = 0,
    AfterCalving,
    Milked
} DailyState;


class Cow : public Cattle {
    friend class CowDailyRoutine;

public:
    Cow(Farm* farm);
    ~Cow();
    void Behavior();

private:
    Farm* farm;
    CowDailyRoutineGenerator* cow_routine_generator;
    DailyState state;
};

#endif
