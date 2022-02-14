//
// Created by TriD on 15.02.2022.
//

#include "../public/gate_control_strategy_factory.h"

#include "../private/pay_on_gate_strategy.h"

#include "../../billing/public/billing_system.h"
#include "../../gates/public/gate.h"

namespace Parking {

// static
std::unique_ptr<GateControlStrategy> GateControlStrategyFactory::createPayOnGate(std::unique_ptr<Billing::BillingSystem> billingSystem,
                                                                                 std::unordered_map<std::string, unsigned int>& carsRegistry,
                                                                                 const boost::optional<BillingInformationListener&>& billingListener) {
    return std::make_unique<PayOnGateStrategy>(std::move(billingSystem), carsRegistry, billingListener);
}

} // namespace Parking