//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_FACTORY_H
#define BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_FACTORY_H

#include <memory>
#include <unordered_map>

#include <boost/optional.hpp>

namespace Billing {
class BillingSystem;
}

namespace Parking {

class BillingInformationListener;

class GateControlStrategy;

class GateControlStrategyFactory {
public:
    static std::unique_ptr<GateControlStrategy> createPayOnGate(std::unique_ptr<Billing::BillingSystem> billingSystem,
                                                                std::unordered_map<std::string, unsigned int>& carsRegistry,
                                                                const boost::optional<BillingInformationListener&>& billingListener);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_FACTORY_H
