#include "stall.h"

void Stall::Enter(Entity *e, unsigned long rcap) {
    Store::Enter(e, rcap);
    Cattle* cattle = dynamic_cast<Cattle*>(e);
    if (cattle != NULL) {
        this->cattle.push_back(cattle);
    }
}
