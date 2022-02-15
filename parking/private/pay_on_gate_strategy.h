//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H
#define BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H

#include <unordered_map>
#include <vector>
#include <boost/optional.hpp>

#include "../public/gate_control_strategy.h"

namespace Billing {
class BillingSystem;
} // namespace Billing

namespace Gates {
class GatesController;
} // namespace Gates

namespace Parking {

class BillingInformationListener;

class PayOnGateStrategy : public GateControlStrategy {
public:
    PayOnGateStrategy(Billing::BillingSystem& billingSystem,
                      std::unordered_map<std::string, unsigned int>& carsRegistry,
                      BillingInformationListener& billingListener, Gates::GatesController& gateController);

    void onCarEntering(std::size_t gateId, const std::string& carId, unsigned int tickId) override;
    void onCarLeaving(std::size_t gateId, const std::string& carId, unsigned int tickId) override;
    void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) override;

private:
    std::unordered_map<std::string, unsigned int>& _carsRegistry;
    std::unordered_map<std::string, unsigned int> _carToGateId;

    Billing::BillingSystem& _billingSystem;
    BillingInformationListener& _billingListener;

    Gates::GatesController& _gateController;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H
