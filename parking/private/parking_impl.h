//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_IMPL_H
#define BOOM_GATE_APPLICATION_PARKING_IMPL_H

#include <memory>
#include <vector>

#include <boost/optional.hpp>

#include "../public/parking.h"
#include "../public/gate_control_strategy.h"

#include "../../payments/public/payment_system.h"
#include "../../billing/public/billing_system.h"

namespace Parking {

class GateControlStrategy;

using GateUPtr = std::unique_ptr<Gates::Gate>;

class ParkingImpl: public Parking {
public:
    explicit ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                         std::unique_ptr<GateControlStrategy> gateControlStrategy,
                         Billing::BillingSystem& billingSystem,
                         Billing::BillingInformationListener& billingInformationListener);

    void tick(EventProducer& eventProducer) override;

private:
    void carEnters(const CarEnterData& data);
    void carLeaves(const CarLeaveData& data);

    void payed(const PaymentData& data);

    void onPaymentEvent(const std::string& carId, const Payments::PaymentResult& result);
    void requestBilling(const RequestBillingData& data);

    std::unique_ptr<Payments::PaymentSystem> _paymentSystem;
    std::unique_ptr<GateControlStrategy> _gateControlStrategy;
    Billing::BillingSystem& _billingSystem;
    Billing::BillingInformationListener& _billingListener;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_IMPL_H
