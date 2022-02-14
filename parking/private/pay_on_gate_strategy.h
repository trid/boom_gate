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
}

namespace Parking {

class BillingInformationListener;

class PayOnGateStrategy : public GateControlStrategy {
public:
    PayOnGateStrategy(std::unique_ptr<Billing::BillingSystem> billingSystem,
                      std::unordered_map<std::string, unsigned int>& carsRegistry,
                      const boost::optional<BillingInformationListener&>& billingListener);

    void onCarEntering(std::size_t gateId, const std::string& carId, unsigned int tickId) override;
    void onCarLeaving(std::size_t gateId, const std::string& carId, unsigned int tickId) override;
    void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) override;
    void addGate(std::unique_ptr<Gates::Gate> gate) override;

private:
    using GateUPtr = std::unique_ptr<Gates::Gate>;

private:
    bool checkGateValid(std::size_t gateId);

    std::vector<GateUPtr> _gates;
    std::unordered_map<std::string, unsigned int>& _carsRegistry;
    std::unordered_map<std::string, unsigned int> _carToGateId;

    std::unique_ptr<Billing::BillingSystem> _billingSystem;
    boost::optional<BillingInformationListener&> _billingListener;

    void releaseGate(size_t gateId);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_GATE_STRATEGY_H
