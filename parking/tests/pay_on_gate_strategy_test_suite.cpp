//
// Created by TriD on 15.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <memory>

#include "tests_shared.h"

#include "../private/pay_on_gate_strategy.h"
#include "../public/parking_error_listener.h"
#include "../../gates/public/gate.h"

namespace Parking::Test {

using namespace testing;

class TimerMock: public Utils::Timer {
public:
    MOCK_METHOD(void, tick, (), (override));
    MOCK_METHOD(unsigned int, getTicks, (), (const, override));
};

class CarRegistryMock: public CarRegistry {
public:
    MOCK_METHOD(void, onCarEnter, (const boost::uuids::uuid&), (override));
    MOCK_METHOD(void, onCarLeft, (const boost::uuids::uuid&), (override));
    MOCK_METHOD(unsigned int, getParkingTime, (const boost::uuids::uuid&), (const override));
    MOCK_METHOD(bool, hasAvailableParkingLots, (), (const override));
};

class GateMock: public Gates::Gate {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    bool isOpen() const override { return true; }
};

class ParkingErrorListenerStub: public ParkingErrorListener {
public:
    void onError(const std::string& description) override {

    }
};

TEST(PayOnGateStrategyTestSuite, carEnteredBilledOnLeaving) {
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    TimerMock timerMock;
    CarRegistryMock carsRegistry;
    auto gateMock = std::make_unique<GateMock>();
    Payments::CurrencyAmount expectedAmount{100, "USD"};

    EXPECT_CALL(*gateMock, open);
    EXPECT_CALL(billingSystemMock, getBill).WillOnce(Return(expectedAmount));
    EXPECT_CALL(billingListenerMock, onBillingInformationProduced);
    EXPECT_CALL(timerMock, getTicks).WillRepeatedly(Return(0));

    ParkingErrorListenerStub parkingErrorListenerStub;
    PayOnGateStrategy strategy{billingSystemMock, carsRegistry, carsRegistry, billingListenerMock, parkingErrorListenerStub};
    strategy.addGate(std::move(gateMock));
    strategy.onCarEntering(0, {});
    strategy.onCarLeaving(0, {});

    ASSERT_EQ(expectedAmount, billingListenerMock.getBilledAmount());
}

TEST(PayOnGateStrategyTestSuite, carLeavesAfterPay) {
    BillingSystemMock billingSystemMock;
    BillingListenerMock billingListenerMock;
    TimerMock timerMock;
    CarRegistryMock carsRegistry;
    auto gateMock = std::make_unique<GateMock>();
    Payments::CurrencyAmount expectedAmount{100, "USD"};

    EXPECT_CALL(*gateMock, open).Times(2);
    EXPECT_CALL(billingSystemMock, getBill).WillOnce(Return(expectedAmount));
    EXPECT_CALL(billingListenerMock, onBillingInformationProduced);
    EXPECT_CALL(timerMock, getTicks).WillRepeatedly(Return(0));

    ParkingErrorListenerStub parkingErrorListenerStub;
    PayOnGateStrategy strategy{billingSystemMock, carsRegistry, carsRegistry, billingListenerMock, parkingErrorListenerStub};
    strategy.addGate(std::move(gateMock));
    strategy.onCarEntering(0, {});
    strategy.onCarLeaving(0, {});
    strategy.onPayment({}, Payments::PaymentResult::Accepted);

    ASSERT_EQ(expectedAmount, billingListenerMock.getBilledAmount());
}

} // namespace Parking::Test