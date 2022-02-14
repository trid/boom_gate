//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_BILLING_INFORMATION_LISTENER_H
#define BOOM_GATE_APPLICATION_BILLING_INFORMATION_LISTENER_H

#include <string>

namespace Parking {

class BillingInformationListener {
public:
    virtual void billedFor(size_t gateId, unsigned int amount) = 0;
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_BILLING_INFORMATION_LISTENER_H
