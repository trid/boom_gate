//
// Created by TriD on 24.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_PLACES_AVAILABILITY_PROVIDER_H
#define BOOM_GATE_APPLICATION_PARKING_PLACES_AVAILABILITY_PROVIDER_H

namespace Parking {

class ParkingPlacesAvailabilityProvider {
public:
    virtual ~ParkingPlacesAvailabilityProvider() = default;

    virtual bool hasAvailableParkingLots() const = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_PLACES_AVAILABILITY_PROVIDER_H
