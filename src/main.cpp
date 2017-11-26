#include "simlib.h"

int main() {
    Print("Life at a dairy farm - an IMS project experiment\n");
    SetOutput("dist/model.out");

    Init(0, 31556926); // 31 556 926s = 1y

    Run();

    return 0;
}
