//
// Created by TriD on 08.02.2022.
//

#include "../parking/public/parking.h"
#include "../parking/public/parking_factory.h"
#include "../payments/public/payment_system.h"
#include "../payments/public/payment_system_factory.h"
#include "../gates/public/gate.h"
#include "../gates/public/gate_factory.h"

#include "private/random_events_producer.h"

int main(int, char**) {
    auto paymentSystem = Payments::PaymentSystemFactory::create();
    auto parking = Parking::ParkingFactory::create(std::move(paymentSystem));
    parking->addGate(Gates::GateFactory::create());
    parking->addGate(Gates::GateFactory::create());
    parking->addGate(Gates::GateFactory::create());

    App::RandomEventsProducer randomEventsProducer(3);

    while (true) {
        parking->tick(randomEventsProducer);
    }

    return 0;
}