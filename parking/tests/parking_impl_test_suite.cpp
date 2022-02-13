//
// Created by TriD on 08.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../private/parking_impl.h"

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

TEST(ParkingImplTestSuite, carEnters) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(Return(Event{EventType::CarEnters, CarEnterData{0}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();

    ParkingImpl parking{std::move(paymentSystem)};
    parking.addGate(std::move(gate));

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, carLeaves) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(Return(Event{EventType::CarLeaves, CarLeaveData{0}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();

    ParkingImpl parking{std::move(paymentSystem)};
    parking.addGate(std::move(gate));

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, payedInCash) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(
            Return(Event{EventType::Payment, PaymentData{Payments::PaymentType::Cash, 0, 200}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();
    EXPECT_CALL(*paymentSystem, pay).Times(1);

    ParkingImpl parking{std::move(paymentSystem)};
    parking.addGate(std::move(gate));

    parking.tick(eventProducer);
}

TEST(ParkingImplTestSuite, payedWithCard) {
    EventProducerMock eventProducer;
    EXPECT_CALL(eventProducer, hasEvents).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(eventProducer, poll).WillOnce(
            Return(Event{EventType::Payment,
                         PaymentData{Payments::PaymentType::CashCard, 0, 200, "1234432112344321"}}));

    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).WillOnce(Return());
    EXPECT_CALL(*gate, close).WillOnce(Return());

    auto paymentSystem = std::make_unique<PaymentSystemMock>();
    EXPECT_CALL(*paymentSystem, pay).Times(1);

    ParkingImpl parking{std::move(paymentSystem)};
    parking.addGate(std::move(gate));

    parking.tick(eventProducer);
}

} // namespace Parking::Test
