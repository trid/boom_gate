//
// Created by TriD on 16.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "tests_shared.h"

#include "../private/pay_on_ticket_machine_strategy.h"
#include "../../gates/public/gate.h"
#include "../public/car_registry.h"

namespace Parking::Test {

using namespace testing;

class TimerMock: public Utils::Timer {
public:
    MOCK_METHOD(void, tick, (), (override));
    MOCK_METHOD(unsigned int, getTicks, (), (const, override));
};

class CarRegistryMock: public CarRegistry {
public:
    MOCK_METHOD(void, addCar, (const std::string&), (override));
    MOCK_METHOD(void, removeCar, (const std::string&), (override));
    MOCK_METHOD(unsigned int, getParkingTime, (const std::string&), (const override));
};

class GateMock: public Gates::Gate {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    bool isOpen() const override { return true; }
};

TEST(PayOnTicketMachineStrategyTestSuite, carEnteredStoppedLeaving) {
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    CarRegistryMock carsRegistry;
    auto gateMock = std::make_unique<GateMock>();

    EXPECT_CALL(*gateMock, open);
    EXPECT_CALL(*gateMock, close).Times(2);
    EXPECT_CALL(billingSystemMock, getBill).Times(0);
    EXPECT_CALL(billingListenerMock, onBillingInformationProduced).Times(0);

    PayOnTicketMachineStrategy strategy{carsRegistry};
    strategy.addGate(std::move(gateMock));
    strategy.onCarEntering(0, "ab123c");
    strategy.onCarLeaving(0, "ab123c");
}

TEST(PayOnTicketMachineStrategyTestSuite, carPayedCanLeave) {
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    CarRegistryMock carsRegistry;
    auto gateMock = std::make_unique<GateMock>();

    EXPECT_CALL(*gateMock, open).Times(2);
    EXPECT_CALL(billingSystemMock, getBill).Times(0);
    EXPECT_CALL(billingListenerMock, onBillingInformationProduced).Times(0);

    PayOnTicketMachineStrategy strategy{carsRegistry};
    strategy.addGate(std::move(gateMock));
    strategy.onCarEntering(0, "ab123c");
    strategy.onPayment("ab123c", Payments::PaymentResult::Accepted);
    strategy.onCarLeaving(0, "ab123c");
}

} // namespace Parking::Test