//
// Created by TriD on 08.02.2022.
//

#include "../public/parking_factory.h"

#include "../private/parking_impl.h"

namespace Parking {

// static
std::unique_ptr<Parking> ParkingFactory::create(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                                                std::unique_ptr<Billing::BillingSystem> billingSystem,
                                                std::unordered_map<std::string, unsigned int>& carsRegistry) {
    return std::make_unique<ParkingImpl>(std::move(paymentSystem), std::move(billingSystem), carsRegistry);
}

} // namespace Parking