#ifndef CATTLE_H
#define CATTLE_H

#include <memory>
#include <string>
#include <simlib.h>
#include "stall.h"
#include "cattle_stat.h"

using namespace std;

class Stall;
class CattleStat;

typedef enum {
    male = 0,
    female
} Sex;

typedef enum {
    calf = 0,
    cow,
    bull
} CattleType;

typedef enum  {
    nan = -1,
    heifer = 0,
    milking,
    before_calving,
    after_calving
} CowType;

/**
 * General class for all cattle
 * @param _id          Assigned identifier on ear
 * @param _cattle_type Whether it is calf, cow (including heifers) or bull
 * @param _cow_type    Different parts in cow's lifecycle
 * @param _sex         Cattle's sex - set automatically for cows and bulls overriding parameter value
 * @param _born_at     Time the cow was born at. Defaults to `now` for calves and bulls, but is overriden by a random
 *                     value from interval 1.3-1.5 year for cows.
 */
class Cattle : public Process {
friend class Stall;
friend class CattleRoutine;

public:
    Cattle(string _id, CattleType _cattle_type, CowType _cow_type, Sex _sex, double _born_at = Time);

    // disable copying
    Cattle(Cattle const&) = delete;
    Cattle& operator=(Cattle const&) = delete;

    void Behavior();

    /**
     * Leave stall if any and terminate process
     */
    void Terminate();

    /**
     * Get cattle's ID
     * @return ear identified number
     */
    string get_id();

    /**
     * Get born_at time
     * @return born_at value
     */
    double get_born_at();

    /**
     * Which lactation is the cow in
     * @return number representing lactation order
     */
    int get_lactation_number();

    /**
     * Which day of lactation is it for this cow
     * @return number representing lactation day
     */
    int get_lactation_day();

    /**
     * Get CattleType
     * @return cattle_type value
     */
    CattleType get_cattle_type();

    /**
     * Get CowType
     * @return cow_type value
     */
    CowType get_cow_type();

    /**
     * Compute milk in litres for 1 milking
     * This value is a linear aproximation of a milking curve and depends
     * on the stage of lactation (time since last calving), cow's age and cow's potential.
     *
     * @return milk produced in litres
     */
    double compute_milk_production();

    /**
     * Cow's body condition - number ranging from <0-1>, where 0 = Dead and 1 = Completely healthy.
     * This is value dependends on age (1 till 3y of age, then lineary declining to expected_lifespan,
     * then declining quadratically)
     *
     * @return [description]
     */
    double body_condition();

    /**
     * Get pointer to
     * @return [description]
     */
    CattleStat* get_statistics();

    /**
     * Age by one 1y
     * This method decides whether the cow should be removed from system and if not, makes her older
     * thus effecting milk production, reproduction amount, etc.
     */
    void age();

private:
    string id;
    double born_at;
    Sex sex;
    CattleType cattle_type;
    bool terminated = false;
    bool in_stall = false;

    /**
     * Exppected time this cattle will live
     */
    double expected_lifespan;

    // cow-specific attributes
    CowType cow_type;
    int lactation_cnt = 0;
    int milkings_count = 1;
    double milking_potential = 1;
    CattleStat* statistics;


    void Enter(shared_ptr<Stall> s, unsigned long ReqCap = 1);
    void Leave(shared_ptr<Stall> s, unsigned long ReqCap = 1);
    // type-specific processes
    void calf_process();
    void cow_process();
};

#endif
