//
// Created by TriD on 15.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "tests_shared.h"

#include "../private/pay_on_gate_strategy.h"
#include "../../gates/public/gate.h"
#include "../../gates/public/gates_controller.h"

namespace Parking::Test {

using namespace testing;

class GateControllerMock: public Gates::GatesController {
public:
    MOCK_METHOD(void, addGate, (std::unique_ptr<Gates::Gate>), (override));
    MOCK_METHOD(void, releaseGate, (std::size_t), (override));
    MOCK_METHOD(void, closeGate, (std::size_t), (override));
};

class TimerMock: public Utils::Timer {
public:
    MOCK_METHOD(void, tick, (), (override));
    MOCK_METHOD(unsigned int, getTicks, (), (const, override));
};

TEST(PayOnGateStrategyTestSuite, carEnteredBilledOnLeaving) {
    GateControllerMock gateControllerMock;
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    TimerMock timerMock;
    std::unordered_map<std::string, unsigned int> carsRegistry;

    EXPECT_CALL(gateControllerMock, closeGate);
    EXPECT_CALL(gateControllerMock, releaseGate);
    EXPECT_CALL(billingSystemMock, getBill).WillOnce(Return(100));
    EXPECT_CALL(billingListenerMock, billedFor);
    EXPECT_CALL(timerMock, getTicks).WillRepeatedly(Return(0));

    PayOnGateStrategy strategy{billingSystemMock, carsRegistry, billingListenerMock, gateControllerMock,
                               timerMock};
    strategy.onCarEntering(0, "ab123c");
    strategy.onCarLeaving(0, "ab123c");

    ASSERT_EQ(100, billingListenerMock.getBilledAmount());
}

TEST(PayOnGateStrategyTestSuite, carLeavesAfterPay) {
    GateControllerMock gateControllerMock;
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    TimerMock timerMock;
    std::unordered_map<std::string, unsigned int> carsRegistry;

    EXPECT_CALL(gateControllerMock, closeGate);
    EXPECT_CALL(gateControllerMock, releaseGate).Times(2);
    EXPECT_CALL(billingSystemMock, getBill).WillOnce(Return(100));
    EXPECT_CALL(billingListenerMock, billedFor);
    EXPECT_CALL(timerMock, getTicks).WillRepeatedly(Return(0));

    PayOnGateStrategy strategy{billingSystemMock, carsRegistry, billingListenerMock, gateControllerMock,
                               timerMock};
    strategy.onCarEntering(0, "ab123c");
    strategy.onCarLeaving(0, "ab123c");
    strategy.onPayment("ab123c", Payments::PaymentResult::Accepted);

    ASSERT_EQ(100, billingListenerMock.getBilledAmount());
}

} // namespace Parking::Test