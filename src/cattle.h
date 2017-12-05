#ifndef CATTLE_H
#define CATTLE_H

#include <memory>
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
    virtual void Behavior() =0;

protected:
    Sex sex;
    Type type;
};

#endif
