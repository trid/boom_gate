//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_BILLING_INFORMATION_LISTENER_H
#define BOOM_GATE_APPLICATION_BILLING_INFORMATION_LISTENER_H

#include <string>

namespace Billing {

class BillingInformationListener {
public:
    virtual ~BillingInformationListener() = default;

    virtual void onBillingInformationProduced(const std::string& accountId, unsigned int amount) = 0;
};

} // namespace Billing

#endif //BOOM_GATE_APPLICATION_BILLING_INFORMATION_LISTENER_H
