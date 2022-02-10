//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_EVENT_DATA_H
#define BOOM_GATE_APPLICATION_EVENT_DATA_H

#include <string>
#include <variant>

#include "../../payments/public/payment_type.h"

namespace Parking {

struct CarEnterData {
    std::size_t gateId;
};

struct CarLeaveData {
    std::size_t gateId;
};

struct PaymentData {
    Payments::PaymentType paymentType;
    std::size_t gateId;
    unsigned int amount;
    std::string cardId;
};

using EventData = std::variant<CarEnterData, CarLeaveData, PaymentData>;

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_EVENT_DATA_H
