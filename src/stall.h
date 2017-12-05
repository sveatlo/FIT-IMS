#ifndef COWS_STALL_H
#define COWS_STALL_H

#include <memory>
#include <vector>
#include <simlib.h>
#include "log.h"
#include "cattle.h"

using namespace std;

class Cattle;

class Stall : public Store {
public:
    Stall(int _cap) : Store(_cap) {};

    void Enter(Entity *e, unsigned long rcap);

private:
    vector<Cattle*> cattle;
};

#endif
