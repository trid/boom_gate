//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_RANDOM_EVENTS_PRODUCER_H
#define BOOM_GATE_APPLICATION_RANDOM_EVENTS_PRODUCER_H

#include <random>

#include "../../billing/public/billing_information_listener.h"
#include "../../parking/public/event_producer.h"

namespace App {

class RandomEventsProducer: public Parking::EventProducer, public Billing::BillingInformationListener {
public:
    explicit RandomEventsProducer(size_t maxGates);

    Parking::Event poll() override;
    bool hasEvents() override;

    void billedFor(size_t gateId, unsigned int amount) override;

private:
    std::default_random_engine _randomEngine;
    std::uniform_int_distribution<std::size_t> _eventDistribution;
    std::uniform_int_distribution<std::size_t> _gatesDistribution;
    std::uniform_int_distribution<unsigned int> _hasEventsDistribution;
    std::uniform_int_distribution<unsigned int> _paymentTypesDistribution;
    std::uniform_int_distribution<unsigned int> _cardIdDistribution;

    Parking::Event makeCarEntersEvent();
    Parking::Event makeCarLeavesEvent();

    Parking::Event makePayEvent();
    Parking::Event makePayEvent(Payments::PaymentType paymentType);
    std::string makeCardId(unsigned int length);

    unsigned int _carsEntered{};
    unsigned int _carsLeaving{};
};

} // namespace App

#endif //BOOM_GATE_APPLICATION_RANDOM_EVENTS_PRODUCER_H
