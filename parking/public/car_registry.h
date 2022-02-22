//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CAR_REGISTRY_H
#define BOOM_GATE_APPLICATION_CAR_REGISTRY_H

#include <string>
#include "car_parking_time_provider.h"

namespace Parking {

class CarRegistry: public CarParkingTimeProvider {
public:
    virtual void addCar(const std::string& accountId) = 0;
    virtual void removeCar(const std::string& accountId) = 0;
};

}

#endif //BOOM_GATE_APPLICATION_CAR_REGISTRY_H
