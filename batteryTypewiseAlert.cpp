#include "batteryTypewiseAlert.hpp"
#include <stdio.h>
#include <unordered_map>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(const BatteryCharacter& batteryChar, double temperatureInCelcius) {
  if (batteryChar.coolingStrategy) {
      return batteryChar.coolingStrategy -> classifyTemperature(temperatureInCelcius);
  } 
  else {
      return NORMAL;
  }
}

void checkAndAlert(
    AlertTarget alertTarget, const BatteryCharacter batteryChar, double temperatureInCelcius) {

  BreachType breachType = classifyTemperatureBreach(batteryChar, temperatureInCelcius);

  std::unordered_map<AlertTarget, void(*)(BreachType)> sendAlertFunctionMap = {
        { TO_CONTROLLER, sendToController },
        { TO_EMAIL, sendToEmail }
    };
    sendAlertFunctionMap[alertTarget](breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  std::unordered_map<BreachType, const char*> breachMessages = {
        { TOO_LOW, "Hi, the temperature is too low" },
        { TOO_HIGH, "Hi, the temperature is too high" }
    };
    if (breachMessages.find(breachType) != breachMessages.end()) {
        printf("To: %s\n", recepient);
        printf("%s\n", breachMessages[breachType]);
    }
}
