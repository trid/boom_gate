//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_EVENT_DATA_H
#define BOOM_GATE_APPLICATION_EVENT_DATA_H

#include <string>
#include <variant>

namespace Parking {

struct CarEnterData {
    std::size_t gateId;
};

struct CarLeaveData {
    std::size_t gateId;
};

struct CashPaymentData {
    std::size_t gateId;
    unsigned int amount;
};

struct CardPaymentData {
    std::size_t gateId;
    unsigned int amount;
    std::string cardNumber;
};

using EventData = std::variant<CarEnterData, CarLeaveData, CashPaymentData, CardPaymentData>;

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_EVENT_DATA_H
