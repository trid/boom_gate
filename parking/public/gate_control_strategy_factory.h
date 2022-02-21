//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_FACTORY_H
#define BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_FACTORY_H

#include <memory>
#include <unordered_map>

#include <boost/optional.hpp>

namespace Billing {
class BillingInformationListener;
class BillingSystem;
} // namespace Billing

namespace Gates {
class GatesController;
} // namespace Gates

namespace Utils {
class Timer;
} // namespace Utils

namespace Parking {

class CarRegistry;
class GateControlStrategy;

class GateControlStrategyFactory {
public:
    static std::unique_ptr<GateControlStrategy>
    createPayOnGate(Billing::BillingSystem& billingSystem, CarRegistry& carsRegistry,
                    Billing::BillingInformationListener& billingListener,
                    Gates::GatesController& gatesController);
    static std::unique_ptr<GateControlStrategy> createPayOnTicketMachine(CarRegistry& carsRegistry,
                                                                         Gates::GatesController& gatesController);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_FACTORY_H
