#ifndef COW_H
#define COW_H

#include <simlib.h>
#include "cattle.h"

class Cow;

class CowDailyRoutineGenerator : public Event {
public:
    CowDailyRoutineGenerator(Cow*);
    void Behavior();
private:
    Cow* cow;
};

class CowDailyRoutine : public Process {
public:
    CowDailyRoutine(Cow*);
    void Behavior();
private:
    Cow* cow;
};


typedef enum {
    NotMilked = 0,
    AfterCalving,
    Milked
} DailyState;

class Cow : private Cattle {
    friend class CowDailyRoutine;

public:
    Cow();
    void Behavior();

private:
    CowDailyRoutineGenerator* cow_routine_generator;
    DailyState state;
};

#endif
