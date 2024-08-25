#include "typewise-alert.h"
#include <stdio.h>

// Define temperature limits for each cooling type
typedef struct {
    CoolingType type;
    int lowerLimit;
    int upperLimit;
} CoolingLimits;

static const CoolingLimits coolingLimits[] = {
    { PASSIVE_COOLING, 0, 35 },
    { HI_ACTIVE_COOLING, 0, 45 },
    { MED_ACTIVE_COOLING, 0, 40 }
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) return TOO_LOW;
    if (value > upperLimit) return TOO_HIGH;
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    for (size_t i = 0; i < sizeof(coolingLimits) / sizeof(coolingLimits[0]); ++i) {
        if (coolingLimits[i].type == coolingType) {
            return inferBreach(temperatureInC, coolingLimits[i].lowerLimit, coolingLimits[i].upperLimit);
        }
    }
    return NORMAL; // Default case if coolingType is invalid
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    if (alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    const char* message = getBreachMessage(breachType);

    if (message) {
        printf("To: %s\n", recipient);
        printf("%s", message);
    }
}

const char* getBreachMessage(BreachType breachType) {
    switch (breachType) {
        case TOO_LOW:
            return "Hi, the temperature is too low\n";
        case TOO_HIGH:
            return "Hi, the temperature is too high\n";
        case NORMAL:
            return NULL;
    }
    return NULL; // Default case
}
