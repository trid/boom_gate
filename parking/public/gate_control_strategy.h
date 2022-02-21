//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_H
#define BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_H

#include <string>
#include <memory>

#include "../../payments/public/payment_result.h"
#include "../../gates/public/gates_defs.h"

namespace Gates {
class Gate;
}

namespace Parking {

class GateControlStrategy {
public:
    virtual ~GateControlStrategy() = default;

    virtual void onCarEntering(std::size_t gateId, const std::string& carId) = 0;
    virtual void onCarLeaving(std::size_t gateId, const std::string& carId) = 0;
    virtual void onPayment(const std::string& carId, Payments::PaymentResult paymentResult) = 0;

    virtual void addGate(Gates::GateUPtr gate) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_H
