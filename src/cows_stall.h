#ifndef COWS_STALL_H
#define COWS_STALL_H

#include <memory>
#include <vector>
#include <simlib.h>
#include "log.h"
#include "cow.h"

using namespace std;

class CowsStall : public Store {
public:
    CowsStall(int _cap) : Store(_cap) {};
    ~CowsStall() {
        Log::debug("stall is being destroyed");
    }

    void new_cow();
private:
    vector<shared_ptr<Cow>> cows;
};

#endif
