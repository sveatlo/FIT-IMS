#ifndef CATTLE_H
#define CATTLE_H

#include <simlib.h>

typedef enum {
    male = 0,
    female
} Sex;

typedef enum {
    calf = 0,
    heifer,
    cow,
    bull
} Type;

class Cattle : public Process {
public:
    Cattle();

protected:
    Sex sex;
    Type type;
};

#endif
