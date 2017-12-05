#ifndef CALF_H
#define CALF_H

#include <memory>
#include <simlib.h>
#include "farm.h"
#include "cattle.h"
#include "calf_routine.h"

using namespace std;

class Farm;
class CalfRoutineGenerator;
class CalfRoutine;


class Calf : public Cattle {
friend class CalfRoutine;
public:
    Calf(Farm* _farm);
    ~Calf();

    void Behavior();

private:
    Farm* farm;
    bool grown_up;
    CalfRoutineGenerator* daily_routine_generator;
};

#endif
