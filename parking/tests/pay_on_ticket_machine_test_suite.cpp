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

TEST(PayOnTicketMachineStrategyTestSuite, carEnteredStoppedLeaving) {
    GateControllerMock gateControllerMock;
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    std::unordered_map<std::string, unsigned int> carsRegistry;

    EXPECT_CALL(gateControllerMock, closeGate);
    EXPECT_CALL(gateControllerMock, releaseGate);
    EXPECT_CALL(billingSystemMock, getBill).Times(0);
    EXPECT_CALL(billingListenerMock, billedFor).Times(0);

    PayOnTicketMachineStrategy strategy{billingSystemMock, carsRegistry, billingListenerMock, gateControllerMock};
    strategy.onCarEntering(0, "ab123c", 0);
    strategy.onCarLeaving(0, "ab123c", 15);
}

TEST(PayOnTicketMachineStrategyTestSuite, carPayedCanLeave) {
    GateControllerMock gateControllerMock;
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    std::unordered_map<std::string, unsigned int> carsRegistry;

    EXPECT_CALL(gateControllerMock, closeGate).Times(0);
    EXPECT_CALL(gateControllerMock, releaseGate).Times(2);
    EXPECT_CALL(billingSystemMock, getBill).Times(0);
    EXPECT_CALL(billingListenerMock, billedFor).Times(0);

    PayOnTicketMachineStrategy strategy{billingSystemMock, carsRegistry, billingListenerMock, gateControllerMock};
    strategy.onCarEntering(0, "ab123c", 0);
    strategy.onPayment("ab123c", Payments::PaymentResult::Accepted);
    strategy.onCarLeaving(0, "ab123c", 15);
}

} // namespace Parking::Test