//
// Created by TriD on 08.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "tests_shared.h"

#include "../public/car_registry.h"
#include "../public/gate_control_strategy_factory.h"
#include "../private/parking_impl.h"
#include "../../gates/public/gate.h"
#include "../../gates/public/gates_controller.h"
#include "../../gates/public/gates_controller_factory.h"
#include "../../shared/public/timer.h"

namespace Parking::Test {

using namespace testing;

class EventProducerMock : public EventProducer {
public:
    MOCK_METHOD(Event, poll, (), (override));
    MOCK_METHOD(bool, hasEvents, (), (override));
};

class PaymentSystemMock : public Payments::PaymentSystem {
public:
    PaymentSystemMock() {
        ON_CALL(*this, pay).WillByDefault(
                [this](Payments::PaymentType paymentType, unsigned int amount, const std::string& paymentData,
                       const Payments::PaymentCallback& callback) {
                    callback(Payments::PaymentResult::Accepted);
                });
    }

    MOCK_METHOD(void, pay,
                (Payments::PaymentType paymentType, unsigned int amount, const std::string& paymentData, Payments::PaymentCallback),
                (override));
};

class GateMock : public Gates::Gate {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(bool, isOpen, (), (const, override));
};

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

TEST(ParkingImplTestSuite, carEnters) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(Return(Event{EventType::CarEnters, CarEnterData{0}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();

    CarRegistryMock carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    TimerMock timer;

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock, *gateController),
                        *billingSystem, billingListenerMock};

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, carLeaves) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(Return(Event{EventType::CarLeaves, CarLeaveData{0}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();

    CarRegistryMock carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    TimerMock timerMock;

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock, *gateController),
                        *billingSystem, billingListenerMock};

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, payedInCash) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(
            Return(Event{EventType::Payment, PaymentData{Payments::PaymentType::Cash, "ab123c", 200}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();
    EXPECT_CALL(*paymentSystem, pay).Times(1);

    CarRegistryMock carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    TimerMock timerMock;

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock, *gateController),
                        *billingSystem, billingListenerMock};

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, payedWithCard) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(
            Return(Event{EventType::Payment,
                         PaymentData{Payments::PaymentType::CashCard, "ab123c", 200, "1234432112344321"}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();
    EXPECT_CALL(*paymentSystem, pay).Times(1);

    CarRegistryMock carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    TimerMock timerMock;

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock, *gateController),
                        *billingSystem, billingListenerMock};

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, carIsBilledWhenLeave) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents)
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll)
            .WillOnce(Return(Event{EventType::CarEnters, CarEnterData{0, "ab123c"}}))
            .WillOnce(Return(Event{EventType::CarLeaves, CarLeaveData{0, "ab123c"}}));

    auto gate = std::make_unique<GateMock>();
    auto paymentSystem = std::make_unique<PaymentSystemMock>();

    auto billingSystem = std::make_unique<BillingSystemMock>();
    EXPECT_CALL(*billingSystem, getBill).WillOnce(Return(100));

    auto billingListener = BillingListenerMock();
    EXPECT_CALL(billingListener, onBillingInformationProduced);

    CarRegistryMock carsRegistry;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    TimerMock timerMock;

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListener, *gateController),
                        *billingSystem, billingListener};

    parking.tick(eventProducer);

    ASSERT_EQ(100, billingListener.getBilledAmount());
}

} // namespace Parking::Test
