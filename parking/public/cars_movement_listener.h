//
// Created by TriD on 24.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CARS_MOVEMENT_LISTENER_H
#define BOOM_GATE_APPLICATION_CARS_MOVEMENT_LISTENER_H

#include <boost/uuid/uuid.hpp>

namespace Parking {

class CarsMovementListener {
public:
    virtual ~CarsMovementListener() = default;

    virtual void onCarEnter(const boost::uuids::uuid& accountId) = 0;
    virtual void onCarLeaved(const boost::uuids::uuid& accountId) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_CARS_MOVEMENT_LISTENER_H
