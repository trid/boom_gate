//
// Created by TriD on 08.02.2022.
//

#include "random_events_producer.h"

namespace App {

RandomEventsProducer::RandomEventsProducer(size_t maxGates):
    _eventDistribution(0, 3),
    _gatesDistribution(0, maxGates - 1),
    _hasEventsDistribution(0, 4)
{

}

Parking::Event RandomEventsProducer::poll() {
    switch (_eventDistribution(_randomEngine)) {
        case 0:
            return makeCarEntersEvent();
            break;
        case 1:
            return makeCarLeavesEvent();
            break;
        case 2:
            return makePayInCashEvent();
            break;
        case 3:
            return makePayWithCardEvent();
            break;
    }
    return makeCarEntersEvent();
}

bool RandomEventsProducer::hasEvents() {
    return _hasEventsDistribution(_randomEngine) != 0;
}

Parking::Event RandomEventsProducer::makeCarEntersEvent() {
    return Parking::Event{Parking::EventType::CarEnters, Parking::CarEnterData{_gatesDistribution(_randomEngine)}};
}

Parking::Event RandomEventsProducer::makeCarLeavesEvent() {
    return Parking::Event{Parking::EventType::CarLeaves, Parking::CarLeaveData{_gatesDistribution(_randomEngine)}};
}

Parking::Event RandomEventsProducer::makePayInCashEvent() {
    return Parking::Event{Parking::EventType::CashPayment, Parking::CashPaymentData{_gatesDistribution(_randomEngine), 200}};
}

Parking::Event RandomEventsProducer::makePayWithCardEvent() {
    return Parking::Event{Parking::EventType::CardPayment, Parking::CardPaymentData{_gatesDistribution(_randomEngine), 200, "1234432112344321"}};;
}

} // namespace App