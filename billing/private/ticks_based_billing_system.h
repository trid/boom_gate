//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_TICKS_BASED_BILLING_SYSTEM_H
#define BOOM_GATE_APPLICATION_TICKS_BASED_BILLING_SYSTEM_H

#include <unordered_map>

#include "../public/billing_system.h"

namespace Billing {

class TicksBasedBillingSystem: public BillingSystem {
public:
    explicit TicksBasedBillingSystem(const std::unordered_map<std::string, unsigned int>& registry);

    unsigned int getBill(const std::string& carId, unsigned int currentTick) override;
private:
    const std::unordered_map<std::string, unsigned int>& _registry;
};

} // namespace Billing

#endif //BOOM_GATE_APPLICATION_TICKS_BASED_BILLING_SYSTEM_H
