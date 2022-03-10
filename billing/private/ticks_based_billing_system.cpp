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

Payments::CurrencyAmount TicksBasedBillingSystem::getBill(const boost::uuids::uuid& accountId) {
    auto timeEntered = _timeProvider.getParkingTime(accountId);
    return {(_timer.getTicks() - timeEntered) * pricePerTick, "USD"};
}

} // namespace Billing