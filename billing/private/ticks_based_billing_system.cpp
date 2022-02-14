//
// Created by TriD on 14.02.2022.
//

#include "ticks_based_billing_system.h"

namespace Billing {

constexpr unsigned int pricePerTick = 10;

TicksBasedBillingSystem::TicksBasedBillingSystem(const std::unordered_map<std::string, unsigned int>& registry) : _registry(
        registry) {}

unsigned int TicksBasedBillingSystem::getBill(const std::string& carId, unsigned int currentTick) {
    auto carData = _registry.find(carId);
    if (carData != _registry.end()) {
        return (currentTick - carData->second) * pricePerTick;
    }
    // TODO: Log that the car somehow teleported to the parking here
    return 0;
}

} // namespace Billing