#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test for BreachType classification
TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(10, 0, 35), NORMAL);
    EXPECT_EQ(inferBreach(-1, 0, 35), TOO_LOW);
    EXPECT_EQ(inferBreach(36, 0, 35), TOO_HIGH);
}

// Test for classifyTemperatureBreach
TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 40), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 25), NORMAL);
}

// Mocking functions to test checkAndAlert
class MockAlertTarget : public AlertTarget {
public:
    MOCK_METHOD(void, sendToController, (BreachType), (override));
    MOCK_METHOD(void, sendToEmail, (BreachType), (override));
};

TEST(TypeWiseAlertTestSuite, CheckAndAlert) {
    MockAlertTarget mock;

    // Expect calls for different alert targets
    EXPECT_CALL(mock, sendToController(TOO_HIGH)).Times(1);
    EXPECT_CALL(mock, sendToEmail(TOO_LOW)).Times(1);

    // Test sending to controller
    checkAndAlert(TO_CONTROLLER, {PASSIVE_COOLING, "BrandX"}, 36);
    // Test sending to email
    checkAndAlert(TO_EMAIL, {HI_ACTIVE_COOLING, "BrandY"}, -1);
}
