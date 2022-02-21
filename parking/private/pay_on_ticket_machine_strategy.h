//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H
#define BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H

#include "../public/gate_control_strategy.h"
#include "../../shared/public/timer.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Billing {
class BillingInformationListener;
class BillingSystem;
} // namespace Billing

namespace Gates {
class GatesController;
} // namespace Gates

namespace Parking {

class PayOnTicketMachineStrategy: public GateControlStrategy{
public:
    PayOnTicketMachineStrategy(Billing::BillingSystem& billingSystem,
                               std::unordered_map<std::string, unsigned int>& carsRegistry,
                               Billing::BillingInformationListener& billingListener,
                               Gates::GatesController& gateController,
                               const Utils::Timer& timer);

    void onCarEntering(std::size_t gateId, const std::string& carId) override;
    void onCarLeaving(std::size_t gateId, const std::string& carId) override;
    void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) override;

private:
    std::unordered_map<std::string, unsigned int>& _carsRegistry;
    std::unordered_set<std::string> _payedCars;

    Billing::BillingSystem& _billingSystem;
    Billing::BillingInformationListener& _billingListener;

    Gates::GatesController& _gateController;

    const Utils::Timer& _timer;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H
