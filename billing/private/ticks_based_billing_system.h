//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_TICKS_BASED_BILLING_SYSTEM_H
#define BOOM_GATE_APPLICATION_TICKS_BASED_BILLING_SYSTEM_H

#include <unordered_map>

#include "../public/billing_system.h"
#include "../../shared/public/timer.h"
#include "../../parking/public/car_registry.h"

namespace Billing {

class TicksBasedBillingSystem: public BillingSystem {
public:
    explicit TicksBasedBillingSystem(const Utils::Timer& timer,
                                     const Parking::CarRegistry& registry);

    unsigned int getBill(const std::string& carId) override;
private:
    const Utils::Timer& _timer;
    const Parking::CarRegistry& _registry;
};

} // namespace Billing

#endif //BOOM_GATE_APPLICATION_TICKS_BASED_BILLING_SYSTEM_H
