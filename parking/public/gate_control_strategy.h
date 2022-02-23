//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_H
#define BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_H

#include <string>
#include <memory>

#include <boost/uuid/uuid.hpp>

#include "../../payments/public/payment_result.h"
#include "../../gates/public/gates_defs.h"

namespace Gates {
class Gate;
}

namespace Parking {

class GateControlStrategy {
public:
    virtual ~GateControlStrategy() = default;

    virtual void onCarEntering(std::size_t gateId, const boost::uuids::uuid& accountId) = 0;
    virtual void onCarLeaving(std::size_t gateId, const boost::uuids::uuid& accountId) = 0;
    virtual void onPayment(const boost::uuids::uuid& accountId, Payments::PaymentResult paymentResult) = 0;

    virtual void addGate(Gates::GateUPtr gate) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_GATE_CONTROL_STRATEGY_H
