//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_H
#define BOOM_GATE_APPLICATION_PARKING_H

#include <memory>

#include "event_producer.h"

namespace Gates {
class Gate;
} // namespace Gates

namespace Parking {

class Parking {
public:
    virtual void tick(EventProducer& eventProducer) = 0;
    virtual void addGate(std::unique_ptr<Gates::Gate> gate) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_H
