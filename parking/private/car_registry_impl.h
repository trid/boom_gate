//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CAR_REGISTRY_IMPL_H
#define BOOM_GATE_APPLICATION_CAR_REGISTRY_IMPL_H

#include <string>
#include <unordered_map>

#include "../public/car_parking_time_provider.h"
#include "../public/car_registry.h"
#include "../../shared/public/timer.h"

namespace Parking {

class CarRegistryImpl: public CarRegistry {
public:
    explicit CarRegistryImpl(const Utils::Timer& timer);

    void addCar(const std::string& accountId) override;
    void removeCar(const std::string& accountId) override;
    unsigned int getParkingTime(const std::string& accountId) const override;

private:
    const Utils::Timer& _timer;
    std::unordered_map<std::string, unsigned int> _carEnteredTime;
};

}

#endif //BOOM_GATE_APPLICATION_CAR_REGISTRY_IMPL_H
