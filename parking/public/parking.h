//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_H
#define BOOM_GATE_APPLICATION_PARKING_H

#include <memory>

#include "../../billing/public/billing_information_listener.h"
#include "event_producer.h"

namespace Gates {
class Gate;
} // namespace Gates

namespace Parking {

class Parking {
public:
    virtual ~Parking() = default;

    virtual void tick(EventProducer& eventProducer) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_H
