#include "shared.h"
#include "farm.h"
#include "cattle_routine.h"

CattleRoutine::CattleRoutine(Cattle* cattle) {
    this->cattle = cattle;
}

void CattleRoutine::Behavior() {
    // calves death rates
    double new_age = Time - this->cattle->get_born_at();
    static double age = new_age;
    if (
        (age <= 3 * DAY && new_age > 3 * DAY) ||
        (age <= 0.5 * YEAR && new_age > 0.5 * YEAR)
    ) {
        age = new_age;
    }

    double r = Random();
    if (this->cattle->get_cattle_type() == calf && (
        (age <= 3 * DAY && r < CALVES_DEATH_3DAYS) ||
        (age > 3 * DAY && age <= 0.5 * YEAR && r < CALVES_DEATH_6MONTHS) ||
        (age > 0.5 * YEAR && age <= 1 * YEAR && r < CALVES_DEATH_1YEAR)
    )) {
        Log::warn("Calf #" + this->cattle->get_id() + " died.");
        Log::error("r = " + to_string(r));
        this->cattle->Terminate();
        this->Terminate();
    }

    switch (this->cattle->get_cattle_type()) {
        case calf:
            this->calf_routine();
            break;
        case cow:
            this->cow_routine();
            break;
        default:
            break;
    }
}

void CattleRoutine::calf_routine() {
    // Log::debug("Calf routine began");

    Enter(*Farm::instance()->employees, 1); // seize 1 caretaker for feeding
    Wait(Time + Uniform(1, 3)); // it takes 1-3 minutes to start feeding the calf
    Leave(*Farm::instance()->employees, 1); // the calf can eat now

    Wait(Time + 30 * MINUTE); // calfs are given 30 minutes for eating

    Enter(*Farm::instance()->employees, 1); // seize 1 caretaker for cleanup
    Wait(Time + Uniform(0, 1)); // it takes 1 or less to clean up after eating
    Leave(*Farm::instance()->employees, 1); // the calf can eat now
}

void CattleRoutine::cow_routine() {
    // Log::debug("Cow routine began");

    // prepare and start milking
    Enter(*Farm::instance()->milking_machines, 1);
    Enter(*Farm::instance()->employees, 1);
    Wait(Uniform(0.5, 0.75) * MINUTE); // it takes 30-45 seconds to start the milking
    Leave(*Farm::instance()->employees, 1);
    // milking
    Wait(Uniform(4, 5) * MINUTE);
    // final desinfection and leave
    Enter(*Farm::instance()->employees, 1);
    Wait(0.25 * MINUTE);
    Leave(*Farm::instance()->employees, 1);
    Leave(*Farm::instance()->milking_machines, 1);
}
