#include "log.h"
#include "cattle.h"
#include "farm.h"

Cattle::Cattle(string _id, CattleType _cattle_type, CowType _cow_type, Sex _sex, double _born_at) {
    this->id = Farm::instance()->get_id() + _id;
    this->born_at = _born_at;
    this->cow_type = nan;
    this->cattle_type = _cattle_type;
    switch (this->cattle_type) {
        case cow:
            this->sex = female;
            this->cow_type = _cow_type;
            if (this->born_at == Time) {
                this->born_at = Time - Uniform(1.33333333, 1.5) * YEAR;
            }
            break;
        case bull:
            this->sex = male;
            break;
        case calf:
            this->sex = _sex;
    }
}

void Cattle::Terminate() {
    this->terminated = true;

    if(this->in_stall) {
        switch (this->cattle_type) {
            case calf:
                Leave(Farm::instance()->calves_stall, 1);
                break;
            case cow:
                Leave(Farm::instance()->cows_stall, 1);
                break;
            default:
                break;
        }
    }

    Process::Terminate();
}

void Cattle::Enter(shared_ptr<Stall> s, unsigned long ReqCap) {
    s->Enter(this, ReqCap);
}

void Cattle::Leave(shared_ptr<Stall> s, unsigned long ReqCap) {
    s->Leave(this, ReqCap);
}

string Cattle::get_id() {
    return this->id;
}

void Cattle::Behavior() {
    while(!this->terminated) {
        switch (this->cattle_type) {
            case cow:
                this->cow_process();
                break;
            case bull:
                Log::info("Bull created");
                this->Terminate();
                break;
            case calf:
                this->calf_process();
                break;
        }
    }
}


void Cattle::calf_process() {
    Log::info("Calf " + this->get_id() + " created");
    if(Farm::instance()->calves_stall->Full()) {
        Log::warn("No place to put calf!!!");
        Wait(7 * DAY); // keep calf temporarily with mother
        if(Farm::instance()->calves_stall->Full()) {
            // still full - calf sold
            Log::warn("Calf without place discarded");
            this->Terminate();
        }
    }
    Enter(Farm::instance()->calves_stall, 1);
    this->in_stall = true;

    if (this->sex == male) {
        // young bulls are kept for 1 years, they are sold afterwards
        Wait(1 * YEAR);
    } else {
        // young heifers are kept as calves until their first rut
        // this usually happens around 21st month for most heifers
        Wait(Uniform(1.33333333, 1.5) * YEAR);
    }

    if (this->sex == male) {
        // Kill it
        Log::info("Selling bull " + this->get_id() + " to butcher");
        this->Terminate();
    } else {
        if(!Farm::instance()->cows_stall->Full()) {
            Log::info("calf " + this->get_id() + " -> heifer @ " + to_string(Time));
            this->cattle_type = cow;
            this->cow_type = heifer;

            Leave(Farm::instance()->calves_stall, 1);
            this->in_stall = false;
        } else {
            // Sell it
            Log::info("no space in cow's stall for heifer " + this->get_id() + " => sell heifer");
            this->Terminate();
        }
    }
}

void Cattle::cow_process() {
    Log::info("Cow created");
    Enter(Farm::instance()->cows_stall, 1);
    Log::info("Cow in stall");

    // TODO: start daily routine based on state

    while(!this->terminated) {
        int tries;
        for (tries = 5; tries > 0; tries--) {
            Wait(28 * DAY);
            if (Random() < 0.9) {
                break;
            }
        }
        if (tries == 0) {
            // cow didn't get pregnant on the last try => to butcher's she goes
            Log::info("Cow " + this->get_id() + " discarded after 5th unsuccessful retry");
            break;
        }

        // pregnant cow
        Log::info("Cow " + this->get_id() + " pregnant on try #" + to_string(5 - tries + 1));

        /* Average gestation period for jersey cows is 278.51 days, but the probabality of calving is
         * equal between 271st and the 285th day. However they have to stop milking 6 weeks before that.
         *
         * In this model we stop milking 6 weeks before the 271st day and then wait 6 weeks + <0-15) days
         * for the calving.
         */
        Wait((271 - 6 * 7) * DAY);
        this->cow_type = before_calving;

        Wait(6 * 7 + Uniform(0, 15));
        if (Random() < 0.95) { // 5% calf death rate after birth
            Farm::instance()->new_calf();
        }
        this->cow_type = after_calving;

        Wait(7 * DAY); // Cannot milk for 1 week
        this->cow_type = milking;
        this->lactation_cnt++;

        Wait(5 * 7 * DAY); // After 6 week from calving we can try a new mating
    }

    this->Terminate();
}


double Cattle::get_born_at() {
    return this->born_at;
}

CattleType Cattle::get_cattle_type() {
    return this->cattle_type;
}

CowType Cattle::get_cow_type() {
    return this->cow_type;
}
