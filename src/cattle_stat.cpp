#include <iostream>
#include "shared.h"
#include "cattle_stat.h"



CattleStat::CattleStat(Cattle* _cattle) {
    this->cattle = _cattle;
    this->lifetime_milk = new Histogram("Lifetime", Time, YEAR, 10);
}

void CattleStat::output() {
    for (auto lactation : this->lactation_stats) {
        lactation.second->statistics_output();
    }
}

void CattleStat::die(double death_time) {
    this->died_at = death_time;
}

void CattleStat::milk(double milk) {
    int n = this->cattle->get_lactation_number();
    if (this->lactation_stats.find(n) == this->lactation_stats.end()) {
        this->lactation_stats[n] = new Lactation();
    }

    this->lactation_stats[n]->milk(this->cattle->get_lactation_day(), milk);
}


void Lactation::milk(int day, double amount) {
    this->histogram[day] += amount;

    this->total += amount;
    if (this->histogram[day] < this->min) {
        this->min = this->histogram[day];
    }
    if (this->histogram[day] > this->max) {
        this->max = this->histogram[day];
    }
    if (this->first_record == -1) {
        this->first_record = Time;
    }
    this->last_record = Time;

}

void Lactation::csv_output() {
    Print("day;amount\n");
    for (auto day : this->histogram) {
        Print("%d;%g", day.first, day.second);
    }
}

void Lactation::statistics_output() {
    Print("=======================================\n");
    Print("= MIN: %g\n", this->min);
    Print("= MAX: %g\n", this->max);
    Print("= TOTAL: %g\n", this->total);
    Print("=======================================\n");
}
