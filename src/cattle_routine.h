#ifndef CATTLE_ROUTINE_H
#define CATTLE_ROUTINE_H

#include <simlib.h>
#include "cattle.h"

class Cattle;

class CattleRoutine : public Process {
public:
    CattleRoutine(Cattle* cattle);
    void Behavior();

private:
    Cattle* cattle;

    void calf_routine();
    void cow_routine();
};

#endif
