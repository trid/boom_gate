//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_FACTORY_H
#define BOOM_GATE_APPLICATION_PARKING_FACTORY_H

#include <memory>
#include <unordered_map>

namespace Payments {
class PaymentSystem;
} // namespace Payments

namespace Billing {
class BillingSystem;
}

namespace Parking {

class BillingInformationListener;
class GateControlStrategy;
class Parking;

class ParkingFactory {
public:
    static std::unique_ptr<Parking> create(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                                           std::unique_ptr<GateControlStrategy> gateControlStrategy,
                                           Billing::BillingSystem& billingSystem,
                                           BillingInformationListener& billingInformationListener);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_FACTORY_H
