#ifndef COOLING_STRATEGY_HPP
#define COOLING_STRATEGY_HPP

#include "batteryTypewiseAlert.hpp"
#include "breachType.hpp"

class CoolingStrategy {
public:
    virtual ~CoolingStrategy() = default;
    virtual BreachType classifyTemperature(double temperatureInCelcius) const = 0;
};

class HiActiveCoolingStrategy : public CoolingStrategy {
public:
    BreachType classifyTemperature(double temperatureInCelcius) const override {
        return inferBreach(temperatureInCelcius, 0, 45);
    }
};

class MedActiveCoolingStrategy : public CoolingStrategy {
public:
    BreachType classifyTemperature(double temperatureInCelcius) const override {
        return inferBreach(temperatureInCelcius, 0, 40);
    }
};

class PassiveCoolingStrategy : public CoolingStrategy {
public:
    BreachType classifyTemperature(double temperatureInCelcius) const override {
        return inferBreach(temperatureInCelcius, 0, 35);
    }
};

#endif // COOLING_STRATEGY_HPP
