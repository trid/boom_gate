//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_IMPL_H
#define BOOM_GATE_APPLICATION_PARKING_IMPL_H

#include <memory>
#include <vector>

#include "../public/parking.h"

#include "../../gates/public/gate.h"
#include "../../payments/public/payment_system.h"

namespace Parking {

class ParkingImpl: public Parking {
public:
    using GateUPtr = std::unique_ptr<Gates::Gate>;

public:
    explicit ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem);

    void addGate(GateUPtr gate) override;

    void tick(EventProducer& eventProducer) override;

private:
    std::vector<GateUPtr> _gates;
    std::unique_ptr<Payments::PaymentSystem> _paymentSystem;

    bool checkGateValid(std::size_t gateId) const;

    void carEnters(CarEnterData& data);
    void carLeaves(CarLeaveData& data);

    void releaseGate(size_t gateId);

    void payed(const PaymentData& data);

    void onPaymentEvent(size_t gateId, const Payments::PaymentResult& result);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_IMPL_H
