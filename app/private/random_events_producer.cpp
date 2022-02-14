//
// Created by TriD on 08.02.2022.
//

#include "random_events_producer.h"

namespace App {

RandomEventsProducer::RandomEventsProducer(size_t maxGates) :
        _eventDistribution(0, 2),
        _gatesDistribution(0, maxGates - 1),
        _hasEventsDistribution(0, 4),
        _paymentTypesDistribution(0, 2),
        _cardIdDistribution(0, 9) {

}

Parking::Event RandomEventsProducer::poll() {
    switch (_eventDistribution(_randomEngine)) {
        case 0:
            return makeCarEntersEvent();
            break;
        case 1:
            if (_carsEntered > 0) {
                return makeCarLeavesEvent();
            }
            break;
        case 2:
            if (_carsLeaving > 0) {
                return makePayEvent();
            }
            break;
    }
    return makeCarEntersEvent();
}

bool RandomEventsProducer::hasEvents() {
    return _hasEventsDistribution(_randomEngine) != 0;
}

Parking::Event RandomEventsProducer::makeCarEntersEvent() {
    ++_carsEntered;
    return Parking::Event{Parking::EventType::CarEnters, Parking::CarEnterData{_gatesDistribution(_randomEngine)}};
}

Parking::Event RandomEventsProducer::makeCarLeavesEvent() {
    --_carsEntered;
    ++_carsLeaving;
    return Parking::Event{Parking::EventType::CarLeaves, Parking::CarLeaveData{_gatesDistribution(_randomEngine)}};
}

Parking::Event RandomEventsProducer::makePayEvent() {
    --_carsLeaving;
    auto paymentType = static_cast<Payments::PaymentType>(_paymentTypesDistribution(_randomEngine));

    return makePayEvent(paymentType);
}

Parking::Event RandomEventsProducer::makePayEvent(Payments::PaymentType paymentType) {
    unsigned int amount = 200;
    std::string id;

    switch (paymentType) {
        case Payments::Cash:
            break;
        case Payments::CashCard:
            id = makeCardId(16);
            break;
        case Payments::SubscriptionCard:
            id = makeCardId(10);
            break;
    }

    return Parking::Event{Parking::EventType::Payment,
                          Parking::PaymentData{
                                  paymentType,
                                  id, amount}};
}

std::string RandomEventsProducer::makeCardId(unsigned int length) {
    std::string result;
    for (unsigned int i = 0; i < length; i++) {
        result += std::to_string(_cardIdDistribution(_randomEngine));
    }
    return result;
}

void RandomEventsProducer::billedFor(size_t gateId, unsigned int amount) {
    // TODO: Add billing info here
}


} // namespace App