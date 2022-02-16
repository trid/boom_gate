//
// Created by TriD on 08.02.2022.
//

#include "../billing/public/billing_system_factory.h"
#include "../billing/public/billing_system.h"
#include "../parking/public/parking.h"
#include "../parking/public/parking_factory.h"
#include "../parking/public/gate_control_strategy.h"
#include "../parking/public/gate_control_strategy_factory.h"
#include "../payments/public/payment_system.h"
#include "../payments/public/payment_system_factory.h"
#include "../gates/public/gate.h"
#include "../gates/public/gate_factory.h"
#include "../gates/public/gates_controller.h"
#include "../gates/public/gates_controller_factory.h"

#include "private/random_events_producer.h"

int main(int, char**) {
    App::RandomEventsProducer randomEventsProducer(3);

    std::unordered_map<std::string, unsigned int> carEnteredTime;
    auto paymentSystem = Payments::PaymentSystemFactory::create();
    auto billingSystem = Billing::BillingSystemFactory::create(carEnteredTime);
    auto gatesController = Gates::GatesControllerFactory::create();
    gatesController->addGate(Gates::GateFactory::create());
    gatesController->addGate(Gates::GateFactory::create());
    gatesController->addGate(Gates::GateFactory::create());
    auto gateControlStrategy = Parking::GateControlStrategyFactory::createPayOnGate(*billingSystem,
                                                                                    carEnteredTime, randomEventsProducer,
                                                                                    *gatesController);
    auto parking = Parking::ParkingFactory::create(std::move(paymentSystem), std::move(gateControlStrategy),
                                                   *billingSystem, randomEventsProducer);

    while (true) {
        parking->tick(randomEventsProducer);
    }

    return 0;
}