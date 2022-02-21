//
// Created by TriD on 15.02.2022.
//

#include "../public/gate_control_strategy_factory.h"

#include "../private/pay_on_gate_strategy.h"
#include "../private/pay_on_ticket_machine_strategy.h"

#include "../../billing/public/billing_system.h"
#include "../../gates/public/gates_controller.h"

namespace Parking {

// static
std::unique_ptr<GateControlStrategy> GateControlStrategyFactory::createPayOnGate(Billing::BillingSystem& billingSystem,
                                                                                 std::unordered_map<std::string, unsigned int>& carsRegistry,
                                                                                 Billing::BillingInformationListener& billingListener,
                                                                                 Gates::GatesController& gatesController,
                                                                                 const Utils::Timer& timer) {
    return std::make_unique<PayOnGateStrategy>(billingSystem, carsRegistry, billingListener, gatesController, timer);
}

std::unique_ptr<GateControlStrategy>
GateControlStrategyFactory::createPayOnTicketMachine(Billing::BillingSystem& billingSystem,
                                                     std::unordered_map<std::string, unsigned int>& carsRegistry,
                                                     Billing::BillingInformationListener& billingListener,
                                                     Gates::GatesController& gatesController,
                                                     const Utils::Timer& timer) {
    return std::make_unique<PayOnTicketMachineStrategy>(billingSystem, carsRegistry, billingListener, gatesController, timer);
}

} // namespace Parking