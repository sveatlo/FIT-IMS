#ifndef COWS_STALL_H
#define COWS_STALL_H

#include <memory>
#include <map>
#include <simlib.h>
#include "log.h"
#include "cattle.h"

using namespace std;

class Cattle;

/**
 * Special store for cattle with a map of saved entities
 * Warning: entering with other entities has no effect.
 * @param _cap Store capacity
 * @param _name Name of the store
 */
class Stall : public Store {
public:
    Stall(int _cap) : Store(_cap) {}
    Stall(const char *_name, unsigned long _cap, bool _autoexpand = false) : Store(_name, _cap) {
        this->autoexpand = _autoexpand;
    }

    void Enter(Entity *e, unsigned long rcap) {(void)e; (void)rcap;};
    void Leave(unsigned long rcap) { (void)rcap; };

    /**
     * Enter store and save cattle
     * @param c   The cattle object to save
     * @param cap How many to save
     */
    void Enter(Cattle *c, unsigned long cap);

    /**
     * Leave store and remove cattle
     * @param c   The cattle to remove
     * @param cap How many to remove
     */
    void Leave(Cattle *c, unsigned long cap);

    map<string, Cattle*> get_cattle();

private:
    map<string, Cattle*> cattle;
    bool autoexpand = false;
};

#endif
