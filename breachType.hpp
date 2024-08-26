#ifndef BREACH_TYPE_HPP
#define BREACH_TYPE_HPP

enum BreachType {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);

#endif // BREACHTYPE_HPP
