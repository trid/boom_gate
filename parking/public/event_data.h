//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_EVENT_DATA_H
#define BOOM_GATE_APPLICATION_EVENT_DATA_H

#include <string>
#include <variant>

#include "../../payments/public/payment_type.h"
#include "../../payments/public/currency_amount.h"

namespace Parking {

struct CarEnterData {
    std::size_t gateId;
    std::string carId;
};

struct CarLeaveData {
    std::size_t gateId;
    std::string carId;
};

struct PaymentData {
    Payments::PaymentType paymentType;
    std::string carId;
    Payments::CurrencyAmount amount;
    std::string cardId;
};

struct RequestBillingData {
    std::string carId;
};

using EventData = std::variant<CarEnterData, CarLeaveData, PaymentData, RequestBillingData>;

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_EVENT_DATA_H
