#include <iostream>
#include "stall.h"

void Stall::Enter(Cattle *c, unsigned long cap) {
    if(this->autoexpand && this->Full()) {
        this->SetCapacity(this->Capacity() + 5);
    }

    Store::Enter(c, cap);
    this->cattle[c->get_id()] = c;
}

void Stall::Leave(Cattle *c, unsigned long cap) {
    Store::Leave(cap);
    Log::debug("Cattle leaving stall");
    auto it = this->cattle.find(c->get_id());
    if(it != this->cattle.end()) {
        this->cattle.erase(it);
    }
}

map<string, Cattle*> Stall::get_cattle() {
    return this->cattle;
}
