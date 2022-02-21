//
// Created by TriD on 16.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "tests_shared.h"

#include "../private/pay_on_ticket_machine_strategy.h"
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

TEST(PayOnTicketMachineStrategyTestSuite, carEnteredStoppedLeaving) {
    GateControllerMock gateControllerMock;
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    TimerMock timerMock;
    std::unordered_map<std::string, unsigned int> carsRegistry;

    EXPECT_CALL(gateControllerMock, closeGate);
    EXPECT_CALL(gateControllerMock, releaseGate);
    EXPECT_CALL(billingSystemMock, getBill).Times(0);
    EXPECT_CALL(billingListenerMock, billedFor).Times(0);
    EXPECT_CALL(timerMock, getTicks()).WillOnce(Return(0));

    PayOnTicketMachineStrategy strategy{billingSystemMock, carsRegistry, billingListenerMock, gateControllerMock,
                                        timerMock};
    strategy.onCarEntering(0, "ab123c");
    strategy.onCarLeaving(0, "ab123c");
}

TEST(PayOnTicketMachineStrategyTestSuite, carPayedCanLeave) {
    GateControllerMock gateControllerMock;
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    TimerMock timerMock;
    std::unordered_map<std::string, unsigned int> carsRegistry;

    EXPECT_CALL(gateControllerMock, closeGate).Times(0);
    EXPECT_CALL(gateControllerMock, releaseGate).Times(2);
    EXPECT_CALL(billingSystemMock, getBill).Times(0);
    EXPECT_CALL(billingListenerMock, billedFor).Times(0);
    EXPECT_CALL(timerMock, getTicks).WillRepeatedly(Return(0));

    PayOnTicketMachineStrategy strategy{billingSystemMock, carsRegistry, billingListenerMock, gateControllerMock,
                                        timerMock};
    strategy.onCarEntering(0, "ab123c");
    strategy.onPayment("ab123c", Payments::PaymentResult::Accepted);
    strategy.onCarLeaving(0, "ab123c");
}

} // namespace Parking::Test