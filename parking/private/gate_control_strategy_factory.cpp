//
// Created by TriD on 15.02.2022.
//

#include "../public/gate_control_strategy_factory.h"

#include "../private/pay_on_gate_strategy.h"
#include "../private/pay_on_ticket_machine_strategy.h"

#include "../../gates/public/gate.h"

namespace Parking {

// static
std::unique_ptr<GateControlStrategy>
GateControlStrategyFactory::createPayOnGate(Billing::BillingSystem& billingSystem, CarRegistry& carsRegistry,
                                            Billing::BillingInformationListener& billingListener,
                                            ParkingErrorListener& parkingErrorListener) {
    return std::make_unique<PayOnGateStrategy>(billingSystem, carsRegistry, billingListener, parkingErrorListener);
}

std::unique_ptr<GateControlStrategy>
GateControlStrategyFactory::createPayOnTicketMachine(CarRegistry& carsRegistry) {
    return std::make_unique<PayOnTicketMachineStrategy>(carsRegistry);
}

} // namespace Parking