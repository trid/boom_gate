//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CAR_REGISTRY_FACTORY_H
#define BOOM_GATE_APPLICATION_CAR_REGISTRY_FACTORY_H

#include <memory>
#include "car_registry.h"
#include "../../shared/public/timer.h"

namespace Parking {

class CarRegistryFactory {
public:
    static std::unique_ptr<CarRegistry> create(const Utils::Timer& timer, unsigned int maxCarsAmount);
};

}

#endif //BOOM_GATE_APPLICATION_CAR_REGISTRY_FACTORY_H
