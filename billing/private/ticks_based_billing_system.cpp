//
// Created by TriD on 14.02.2022.
//

#include "ticks_based_billing_system.h"

namespace Billing {

constexpr unsigned int pricePerTick = 10;

TicksBasedBillingSystem::TicksBasedBillingSystem(const Utils::Timer& timer,
                                                 const Parking::CarParkingTimeProvider& timeProvider)
        : _timer(timer),
          _timeProvider(timeProvider) {}

unsigned int TicksBasedBillingSystem::getBill(const std::string& carId) {
    auto timeEntered = _timeProvider.getParkingTime(carId);
    return (_timer.getTicks() - timeEntered) * pricePerTick;
}

} // namespace Billing