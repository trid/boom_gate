//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_IMPL_H
#define BOOM_GATE_APPLICATION_PARKING_IMPL_H

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include "../public/parking.h"

#include "../../gates/public/gate.h"
#include "../../payments/public/payment_system.h"
#include "../../billing/public/billing_system.h"

namespace Parking {

class ParkingImpl: public Parking {
public:
    using GateUPtr = std::unique_ptr<Gates::Gate>;

public:
    explicit ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                         std::unique_ptr<Billing::BillingSystem> billingSystem,
                         std::unordered_map<std::string, unsigned int>& carsRegistry);

    void addGate(GateUPtr gate) override;

    void tick(EventProducer& eventProducer) override;

    void setBillingListener(BillingInformationListener& billingListener) override;

private:
    bool checkGateValid(std::size_t gateId) const;

    void carEnters(CarEnterData& data);
    void carLeaves(CarLeaveData& data);

    void releaseGate(size_t gateId);

    void payed(const PaymentData& data);

    void onPaymentEvent(size_t gateId, const Payments::PaymentResult& result);

    std::vector<GateUPtr> _gates;
    std::unique_ptr<Payments::PaymentSystem> _paymentSystem;
    std::unique_ptr<Billing::BillingSystem> _billingSystem;
    boost::optional<BillingInformationListener&> _billingListener;
    unsigned int _tickNumber = 0;
    std::unordered_map<std::string, unsigned int>& _carsRegistry;
    std::unordered_map<unsigned int, std::string> _gateToCarMap;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_IMPL_H
