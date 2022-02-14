//
// Created by TriD on 14.02.2022.
//

#include "../public/billing_system_factory.h"

#include "ticks_based_billing_system.h"

namespace Billing {

// static
std::unique_ptr<BillingSystem> BillingSystemFactory::create(const std::unordered_map<std::string, unsigned int>& registry) {
    return std::make_unique<TicksBasedBillingSystem>(registry);
}

} // namespace Billing
