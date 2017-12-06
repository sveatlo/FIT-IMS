#ifndef COWS_STALL_H
#define COWS_STALL_H

#include <memory>
#include <map>
#include <simlib.h>
#include "log.h"
#include "cattle.h"

using namespace std;

class Cattle;

class Stall : public Store {
public:
    Stall(int _cap);

    void Enter(Entity *e, unsigned long rcap) {(void)e; (void)rcap;};
    void Leave(unsigned long rcap) { (void)rcap; };

    void Enter(Cattle *c, unsigned long cap);
    void Leave(Cattle *c, unsigned long cap);

    map<string, Cattle*> get_cattle();

private:
    map<string, Cattle*> cattle;
};

#endif
