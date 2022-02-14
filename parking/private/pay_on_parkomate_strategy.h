//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAY_ON_PARKOMATE_STRATEGY_H
#define BOOM_GATE_APPLICATION_PAY_ON_PARKOMATE_STRATEGY_H

#include "../public/gate_control_strategy.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Billing {
class BillingSystem;
}

namespace Parking {

class BillingInformationListener;

using GateUPtr = std::unique_ptr<Gates::Gate>;

class PayOnParkomateStrategy: public GateControlStrategy{
public:
    PayOnParkomateStrategy(std::unordered_map<std::string, unsigned int>& carsRegistry,
                           Billing::BillingSystem& billingSystem, BillingInformationListener& billingListener);

    void onCarEntering(std::size_t gateId, const std::string& carId, unsigned int tickId) override;
    void onCarLeaving(std::size_t gateId, const std::string& carId, unsigned int tickId) override;
    void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) override;
    void addGate(std::unique_ptr<Gates::Gate> gate) override;

private:
    std::vector<GateUPtr> _gates;
    std::unordered_map<std::string, unsigned int>& _carsRegistry;
    std::unordered_set<std::string> _payedCars;

    Billing::BillingSystem& _billingSystem;
    BillingInformationListener& _billingListener;

    void checkGateValid(size_t gateId);

    void releaseGate(size_t gateId);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_PARKOMATE_STRATEGY_H
