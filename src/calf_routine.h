#ifndef CALF_ROUTINE_H
#define CALF_ROUTINE_H

#include <simlib.h>
#include "calf.h"

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

#endif
