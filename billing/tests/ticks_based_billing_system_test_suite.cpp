//
// Created by TriD on 14.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../private/ticks_based_billing_system.h"
#include "../../parking/public/car_registry.h"

class TimerMock: public Utils::Timer {
public:
    MOCK_METHOD(void, tick, (), (override));
    MOCK_METHOD(unsigned int, getTicks, (), (const, override));
};

class CarRegistryMock: public Parking::CarRegistry {
public:
    MOCK_METHOD(void, addCar, (const std::string&), (override));
    MOCK_METHOD(void, removeCar, (const std::string&), (override));
    MOCK_METHOD(unsigned int, getParkingTime, (const std::string&), (const override));
};

namespace Billing::Tests {

TEST(TicksBasedBillingSystemTestSuite, billCarForSpentTime) {
    constexpr char carId[] = "ab123c";
    TimerMock timerMock;
    CarRegistryMock carRegistryMock;

    EXPECT_CALL(timerMock, getTicks).WillOnce(testing::Return(5));
    EXPECT_CALL(carRegistryMock, getParkingTime).WillOnce(testing::Return(0));

    TicksBasedBillingSystem billingSystem{timerMock, carRegistryMock};
    auto billedAmount = billingSystem.getBill(carId);

    ASSERT_EQ(50, billedAmount);
}

} // namespace Billing::Tests