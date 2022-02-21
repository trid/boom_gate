//
// Created by TriD on 08.02.2022.
//

#include "private/tick_timer.h"
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

class BillingInformationListenerStub : public Billing::BillingInformationListener {
public:
    void billedFor(size_t gateId, unsigned int amount) override {

    }
};


int main(int, char**) {
    TickTimer timer;
    std::unordered_map<std::string, unsigned int> carEnteredTime;
    auto paymentSystem = Payments::PaymentSystemFactory::create();
    auto billingSystem = Billing::BillingSystemFactory::create(timer, carEnteredTime);
    auto gatesController = Gates::GatesControllerFactory::create();
    gatesController->addGate(Gates::GateFactory::create());
    gatesController->addGate(Gates::GateFactory::create());
    gatesController->addGate(Gates::GateFactory::create());
    BillingInformationListenerStub billingInformationListenerStub;
    auto gateControlStrategy = Parking::GateControlStrategyFactory::createPayOnGate(*billingSystem,
                                                                                    carEnteredTime,
                                                                                    billingInformationListenerStub,
                                                                                    *gatesController, timer);
    auto parking = Parking::ParkingFactory::create(std::move(paymentSystem), std::move(gateControlStrategy),
                                                   *billingSystem, billingInformationListenerStub);

    return 0;
}