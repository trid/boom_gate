//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_BILLING_SYSTEM_H
#define BOOM_GATE_APPLICATION_BILLING_SYSTEM_H

#include <string>

#include <boost/uuid/uuid.hpp>

#include "../../payments/public/currency_amount.h"

namespace Billing {

class BillingSystem {
public:
    virtual ~BillingSystem() = default;

    virtual Payments::CurrencyAmount getBill(const boost::uuids::uuid& accountId) = 0;
};

} // namespace Billing

#endif //BOOM_GATE_APPLICATION_BILLING_SYSTEM_H
