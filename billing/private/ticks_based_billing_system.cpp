//
// Created by TriD on 14.02.2022.
//

#include "ticks_based_billing_system.h"

namespace Billing {

constexpr unsigned int pricePerTick = 10;

TicksBasedBillingSystem::TicksBasedBillingSystem(const Utils::Timer& timer,
                                                 const Parking::CarRegistry& registry)
        : _timer(timer),
        _registry(registry) {}

unsigned int TicksBasedBillingSystem::getBill(const std::string& carId) {
    auto timeEntered = _registry.getParkingTime(carId);
    return (_timer.getTicks() - timeEntered) * pricePerTick;
}

} // namespace Billing