//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H
#define BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H

#include "../public/gate_control_strategy.h"
#include "../../shared/public/timer.h"
#include "../public/car_registry.h"
#include "gate_controller_base.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Billing {
class BillingInformationListener;
class BillingSystem;
} // namespace Billing


namespace Parking {

class PayOnTicketMachineStrategy: public GateControlStrategy, private GateControllerBase{
public:
    explicit PayOnTicketMachineStrategy(CarRegistry& carsRegistry);

    void onCarEntering(std::size_t gateId, const std::string& carId) override;
    void onCarLeaving(std::size_t gateId, const std::string& carId) override;
    void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) override;

    void addGate(Gates::GateUPtr gate) override;

private:
    CarRegistry& _carsRegistry;
    std::unordered_set<std::string> _payedCars;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H
