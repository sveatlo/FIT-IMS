#ifndef CATTLE_H
#define CATTLE_H

#include <memory>
#include <string>
#include <simlib.h>
#include "stall.h"

using namespace std;

class Stall;

typedef enum {
    male = 0,
    female
} Sex;

typedef enum {
    calf = 0,
    cow,
    bull
} CattleType;

typedef enum  {
    nan = -1,
    heifer = 0,
    milking,
    before_calving,
    after_calving
} CowType;

class Cattle : public Process {
friend class Stall;

public:
    Cattle(string _id, CattleType _cattle_type, CowType _cow_type, Sex _sex, double _born_at = Time);
    void Behavior();
    void Terminate();

    string get_id();
    double get_born_at();
    CattleType get_cattle_type();
    CowType get_cow_type();

private:
    string id;
    double born_at;
    Sex sex;
    CattleType cattle_type;
    bool terminated = false;
    bool in_stall = false;

    // cow-specific attributes
    CowType cow_type;
    int lactation_cnt = 0;

    void Enter(shared_ptr<Stall> s, unsigned long ReqCap = 1);
    void Leave(shared_ptr<Stall> s, unsigned long ReqCap = 1);
    // type-specific processes
    void calf_process();
    void cow_process();
};

#endif
