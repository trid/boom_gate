//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CAR_REGISTRY_IMPL_H
#define BOOM_GATE_APPLICATION_CAR_REGISTRY_IMPL_H

#include <string>
#include <unordered_map>

#include <boost/functional/hash.hpp>

#include "../public/car_parking_time_provider.h"
#include "../public/car_registry.h"
#include "../../shared/public/timer.h"

namespace Parking {

class CarRegistryImpl: public CarRegistry {
public:
    explicit CarRegistryImpl(const Utils::Timer& timer);

    void addCar(const boost::uuids::uuid& accountId) override;
    void removeCar(const boost::uuids::uuid& accountId) override;
    unsigned int getParkingTime(const boost::uuids::uuid& accountId) const override;

private:
    const Utils::Timer& _timer;
    std::unordered_map<boost::uuids::uuid, unsigned int, boost::hash<boost::uuids::uuid>> _carEnteredTime;
};

}

#endif //BOOM_GATE_APPLICATION_CAR_REGISTRY_IMPL_H
