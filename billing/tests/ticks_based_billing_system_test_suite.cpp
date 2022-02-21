//
// Created by TriD on 14.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../private/ticks_based_billing_system.h"

class TimerMock: public Utils::Timer {
public:
    MOCK_METHOD(void, tick, (), (override));
    MOCK_METHOD(unsigned int, getTicks, (), (const, override));
};

namespace Billing::Tests {

TEST(TicksBasedBillingSystemTestSuite, billCarForSpentTime) {
    std::unordered_map<std::string, unsigned int> registry;
    constexpr char carId[] = "ab123c";
    registry.emplace(carId, 0);
    TimerMock timerMock;
    EXPECT_CALL(timerMock, getTicks).WillOnce(testing::Return(5));

    TicksBasedBillingSystem billingSystem{timerMock, registry};
    auto billedAmount = billingSystem.getBill(carId);

    ASSERT_EQ(50, billedAmount);
}

} // namespace Billing::Tests