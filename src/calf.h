#ifndef CALF_H
#define CALF_H

#include "cattle.h"

using namespace std;

class Calf;

class CalfRoutineGenerator : public Event {
public:
    CalfRoutineGenerator(Calf*);
    void Behavior();

private:
    Calf* calf;
};

class CalfRoutine : public Process {
public:
    CalfRoutine(Calf*);
    void Behavior();

private:
    Calf* calf;
};

class Calf : public Cattle {
public:
    Calf(Sex sex);

    void Behavior();

private:
    CalfRoutineGenerator* daily_routine_generator;
};

#endif
