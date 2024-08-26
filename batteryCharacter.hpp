#ifndef BATTERY_CHARACTER_HPP
#define BATTERY_CHARACTER_HPP

#include "coolingStrategy.hpp"

struct BatteryCharacter {
    CoolingStrategy* coolingStrategy;
    char brand[48];
};

#endif // BATTERY_CHARACTER_HPP
