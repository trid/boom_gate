//
// Created by TriD on 14.02.2022.
//

#include "../public/billing_system_factory.h"

#include "ticks_based_billing_system.h"

namespace Billing {

// static
std::unique_ptr<BillingSystem>
BillingSystemFactory::create(const Utils::Timer& timer, const Parking::CarRegistry& registry) {
    return std::make_unique<TicksBasedBillingSystem>(timer, registry);
}

} // namespace Billing
