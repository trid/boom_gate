//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_EVENT_DATA_H
#define BOOM_GATE_APPLICATION_EVENT_DATA_H

#include <string>
#include <variant>

#include <boost/uuid/uuid.hpp>

#include "../../payments/public/payment_type.h"
#include "../../payments/public/currency_amount.h"

namespace Parking {

struct CarEnterData {
    std::size_t gateId;
    boost::uuids::uuid accountId;
};

struct CarLeaveData {
    std::size_t gateId;
    boost::uuids::uuid accountId;
};

struct PaymentData {
    Payments::PaymentType paymentType;
    boost::uuids::uuid accountId;
    Payments::CurrencyAmount amount;
    std::string cardId;
};

struct RequestBillingData {
    boost::uuids::uuid accountId;
};

using EventData = std::variant<CarEnterData, CarLeaveData, PaymentData, RequestBillingData>;

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_EVENT_DATA_H
