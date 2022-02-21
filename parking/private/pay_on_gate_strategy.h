//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H
#define BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H

#include <unordered_map>
#include <vector>
#include <boost/optional.hpp>

#include "../public/gate_control_strategy.h"
#include "../../shared/public/timer.h"
#include "../public/car_registry.h"
#include "gate_controller_base.h"

namespace Billing {
class BillingInformationListener;
class BillingSystem;
} // namespace Billing

namespace Gates {
class GatesController;
} // namespace Gates

namespace Parking {

class PayOnGateStrategy : public GateControlStrategy, private GateControllerBase {
public:
    PayOnGateStrategy(Billing::BillingSystem& billingSystem, CarRegistry& carsRegistry,
                      Billing::BillingInformationListener& billingListener);

    void onCarEntering(std::size_t gateId, const std::string& carId) override;
    void onCarLeaving(std::size_t gateId, const std::string& carId) override;
    void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) override;

    void addGate(Gates::GateUPtr gate) override;

private:
    CarRegistry& _carsRegistry;
    std::unordered_map<std::string, unsigned int> _carToGateId;

    Billing::BillingSystem& _billingSystem;
    Billing::BillingInformationListener& _billingListener;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H
