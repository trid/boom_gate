//
// Created by TriD on 21.02.2022.
//

#include "car_registry_impl.h"

Parking::CarRegistryImpl::CarRegistryImpl(const Utils::Timer& timer) : _timer(timer) {}

void Parking::CarRegistryImpl::addCar(const std::string& accountId) {
    _carEnteredTime[accountId] = _timer.getTicks();
}

void Parking::CarRegistryImpl::removeCar(const std::string& accountId) {
    _carEnteredTime.erase(accountId);
}

unsigned int Parking::CarRegistryImpl::getParkingTime(const std::string& accountId) const {
    if (auto it = _carEnteredTime.find(accountId); it != _carEnteredTime.end()) {
        return it->second;
    }
    // TODO (Guess what?) process an error here
    return 0;
}
