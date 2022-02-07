//
// Created by TriD on 07.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_EVENT_H
#define BOOM_GATE_APPLICATION_EVENT_H

#include "event_data.h"
#include "event_type.h"

namespace Parking {

struct Event {
    EventType type;
    EventData eventData;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_EVENT_H
