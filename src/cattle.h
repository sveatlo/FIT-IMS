#ifndef CATTLE_H
#define CATTLE_H

#include <memory>
#include <string>
#include <simlib.h>
#include "farm.h"
#include "calf_routine.h"

using namespace std;

class Farm;
class CalfRoutineGenerator;
class CalfRoutine;

typedef enum {
    male = 0,
    female
} Sex;

typedef enum {
    calf = 0,
    heifer,
    cow,
    bull
} Type;

class Cattle : public Process {
friend class CalfRoutineGenerator;
friend class CalfRoutine;

public:
    void Behavior();
    Cattle(Farm* _farm, string _id, Type _type, Sex _sex, double _born_at = Time);

private:
    double born_at;
    string id;
    Sex sex;
    Type type;
    Farm* farm;

    // processes
    CalfRoutineGenerator* calf_routine_generator;
};

#endif
