//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_EVENT_PRODUCER_H
#define BOOM_GATE_APPLICATION_EVENT_PRODUCER_H

#include "event.h"

namespace Parking {

class EventProducer {
public:
    virtual Event poll() = 0;
    virtual bool hasEvents() = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_EVENT_PRODUCER_H
