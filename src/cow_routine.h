#ifndef COW_ROUTINE_H
#define COW_ROUTINE_H

#include <simlib.h>
#include "cow.h"

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

#endif
