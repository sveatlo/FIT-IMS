#include "log.h"
#include "cattle.h"

Cattle::Cattle(Farm* _farm, string _id, Type _type, Sex _sex, double _born_at) {
    this->farm = _farm;
    this->id = this->farm->get_id() + _id;
    this->born_at = _born_at;
    this->type = _type;
    switch (this->type) {
        case heifer:
        case cow:
            this->sex = female;
            break;
        case bull:
            this->sex = male;
            break;
        default:
            this->sex = _sex;
    }
}


void Cattle::Behavior() {
    switch (this->type) {
        case heifer:
            Log::info("Heifer created");
            break;
        case cow:
            Log::info("Cow created");
            break;
        case bull:
            Log::info("Bull created");
            break;
        case calf:
            Log::info("Calf created");

            this->calf_routine_generator = new CalfRoutineGenerator(this);

            if (this->sex == male) {
                // young bulls are kept for 1 years, they are sold afterwards
                Wait(1 * YEAR);
            } else {
                // young heifers are kept as calves until their first rut
                // this usually happens around 21st month for most heifers
                Wait(Normal(1.75, 0.25) * YEAR);
            }
            this->calf_routine_generator->Passivate();

            if (this->sex == male) {
                // Kill it
                Log::info("Selling bull to butcher");
                this->Terminate();
            } else {
                if(!this->farm->stall->Full()) {
                    Log::info("calf -> heifer");
                    this->type = heifer;
                    this->Activate();
                } else {
                    // Sell it
                    Log::info("no space in stall for cows => sell heifer");
                    this->Terminate();
                }
            }

            break;
    }
}
