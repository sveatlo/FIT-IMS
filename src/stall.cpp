#include <iostream>
#include "stall.h"

Stall::Stall(int _cap) : Store(_cap) { };

void Stall::Enter(Cattle *c, unsigned long cap) {
    Store::Enter(c, cap);
    this->cattle[c->get_id()] = c;
}

void Stall::Leave(Cattle *c, unsigned long cap) {
    Store::Leave(cap);
    auto it = this->cattle.find(c->get_id());
    if(it != this->cattle.end()) {
        this->cattle.erase(it);
    }
}

map<string, Cattle*> Stall::get_cattle() {
    return this->cattle;
}
