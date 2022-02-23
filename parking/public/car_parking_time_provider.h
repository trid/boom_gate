//
// Created by TriD on 23.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CAR_PARKING_TIME_PROVIDER_H
#define BOOM_GATE_APPLICATION_CAR_PARKING_TIME_PROVIDER_H

#include <string>

#include <boost/uuid/uuid.hpp>

namespace Parking {

class CarParkingTimeProvider {
public:
    virtual ~CarParkingTimeProvider() = default;

    [[nodiscard]] virtual unsigned int getParkingTime(const boost::uuids::uuid& accountId) const = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_CAR_PARKING_TIME_PROVIDER_H
