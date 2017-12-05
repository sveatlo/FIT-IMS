#include <iostream>
#include <simlib.h>
#include "log.h"
#include "shared.h"
#include "farm.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    Log::info("Life at a dairy farm - an IMS project experiment");
    SetOutput("dist/model.out");
    Init(0, 4 * YEAR);

    (new Farm(1, 1, 0, 1, 1))->Activate();

    Run();

    return 0;
}
