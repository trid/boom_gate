//
// Created by TriD on 21.02.2022.
//

#include "../public/car_registry_factory.h"

#include "car_registry_impl.h"

namespace Parking {

// static
std::unique_ptr<CarRegistry> CarRegistryFactory::create(const Utils::Timer& timer) {
    return std::make_unique<CarRegistryImpl>(timer);
}

}