#include <iostream>
#include <memory>
#include <simlib.h>
#include "shared.h"
#include "log.h"
#include "calf.h"


using namespace std;

class FarmGenerator : public Event {
     void Behavior() {
         (new Calf(female))->Activate();
     }
};

int main() {
    Log::info("Life at a dairy farm - an IMS project experiment");

    SetOutput("dist/model.out");
    Init(0, 4 * YEAR); // 31 556 926s = 1y

    (new FarmGenerator)->Activate();

    Run();

    return 0;
}
