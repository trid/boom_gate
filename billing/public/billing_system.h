//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_BILLING_SYSTEM_H
#define BOOM_GATE_APPLICATION_BILLING_SYSTEM_H

#include <string>

namespace Billing {

class BillingSystem {
public:
    virtual ~BillingSystem() = default;

    virtual unsigned int getBill(const std::string& carId) = 0;
};

} // namespace Billing

#endif //BOOM_GATE_APPLICATION_BILLING_SYSTEM_H
