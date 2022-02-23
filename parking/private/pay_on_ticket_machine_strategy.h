//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H
#define BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/functional/hash.hpp>

#include "../public/gate_control_strategy.h"
#include "../../shared/public/timer.h"
#include "../public/car_registry.h"
#include "gate_controller_base.h"


namespace Billing {
class BillingInformationListener;
class BillingSystem;
} // namespace Billing


namespace Parking {

class PayOnTicketMachineStrategy: public GateControlStrategy, private GateControllerBase{
public:
    explicit PayOnTicketMachineStrategy(CarRegistry& carsRegistry);

    void onCarEntering(std::size_t gateId, const boost::uuids::uuid& accountId) override;
    void onCarLeaving(std::size_t gateId, const boost::uuids::uuid& accountId) override;
    void onPayment(const boost::uuids::uuid& accountId, Payments::PaymentResult paymentResult) override;

    void addGate(Gates::GateUPtr gate) override;

private:
    CarRegistry& _carsRegistry;
    std::unordered_set<boost::uuids::uuid, boost::hash<boost::uuids::uuid>> _payedCars;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PAY_ON_TICKET_MACHINE_STRATEGY_H
