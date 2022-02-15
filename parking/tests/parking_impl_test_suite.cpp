//
// Created by TriD on 08.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../public/gate_control_strategy_factory.h"
#include "../private/parking_impl.h"
#include "../../gates/public/gate.h"
#include "../../gates/public/gates_controller.h"
#include "../../gates/public/gates_controller_factory.h"

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

class BillingSystemMock : public Billing::BillingSystem {
public:
    MOCK_METHOD(unsigned int, getBill, (const std::string&, unsigned int), (override));
};

class BillingListenerMock : public BillingInformationListener {
public:
    BillingListenerMock() {
        ON_CALL(*this, billedFor).WillByDefault(
                [this](size_t, unsigned int amount) {
                    _billedAmount = amount;
                });
    }

    unsigned int getBilledAmount() const {
        return _billedAmount;
    }

    MOCK_METHOD(void, billedFor, (size_t, unsigned int), (override));
private:
    unsigned int _billedAmount = 0;
};

class GateMock : public Gates::Gate {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(bool, isOpen, (), (const, override));
};

TEST(ParkingImplTestSuite, carEnters) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(Return(Event{EventType::CarEnters, CarEnterData{0}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();

    std::unordered_map<std::string, unsigned int> carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock,  *gateController),
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

    std::unordered_map<std::string, unsigned int> carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock,  *gateController),
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

    std::unordered_map<std::string, unsigned int> carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock,  *gateController),
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

    std::unordered_map<std::string, unsigned int> carsRegistry;
    auto billingSystem = std::make_unique<BillingSystemMock>();
    BillingListenerMock billingListenerMock;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListenerMock,  *gateController),
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
    EXPECT_CALL(billingListener, billedFor);

    std::unordered_map<std::string, unsigned int> carsRegistry;

    auto gateController = Gates::GatesControllerFactory::create();
    gateController->addGate(std::move(gate));

    ParkingImpl parking{std::move(paymentSystem),
                        GateControlStrategyFactory::createPayOnGate(*billingSystem, carsRegistry,
                                                                    billingListener,  *gateController),
                        *billingSystem, billingListener};

    parking.tick(eventProducer);

    ASSERT_EQ(100, billingListener.getBilledAmount());
}

} // namespace Parking::Test
