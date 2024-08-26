#ifndef BATTERY_TYPEWISE_ALERT_HPP
#define BATTERY_TYPEWISE_ALERT_HPP

#include "coolingStrategy.hpp"
#include "batteryCharacter.hpp"
#include "breachType.hpp"

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

BreachType classifyTemperatureBreach(const BatteryCharacter& batteryChar, double temperatureInCelcius);

void checkAndAlert(
  AlertTarget alertTarget, const BatteryCharacter batteryChar, double temperatureInCelcius);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

typedef void (*AlertFunction)(BreachType);

#endif //BATTERY_TYPEWISE_ALERT_HPP
