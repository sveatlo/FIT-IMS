#ifndef CALF_ROUTINE_H
#define CALF_ROUTINE_H

#include <simlib.h>
#include "cattle.h"

class Cattle;

class CalfRoutineGenerator : public Event {
public:
    CalfRoutineGenerator(Cattle*);
    void Behavior();

private:
    Cattle* calf;
};

class CalfRoutine : public Process {
public:
    CalfRoutine(Cattle*);
    void Behavior();

private:
    Cattle* calf;
};

#endif
