//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CAR_REGISTRY_H
#define BOOM_GATE_APPLICATION_CAR_REGISTRY_H

#include <string>

#include "cars_movement_listener.h"
#include "car_parking_time_provider.h"
#include "parking_places_availability_provider.h"

namespace Parking {

class CarRegistry: public CarParkingTimeProvider, public ParkingPlacesAvailabilityProvider, public CarsMovementListener {
};

}

#endif //BOOM_GATE_APPLICATION_CAR_REGISTRY_H
