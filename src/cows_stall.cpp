#include "cows_stall.h"

void CowsStall::new_cow() {
    shared_ptr<Cow> cow = make_shared<Cow>();
    cow->Activate();
    this->cows.push_back(cow);
}
