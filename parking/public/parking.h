//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_H
#define BOOM_GATE_APPLICATION_PARKING_H

#include "event_producer.h"

namespace Parking {

class Parking {
public:
    virtual void tick(EventProducer& eventProducer) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_H
