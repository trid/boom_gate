//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_H
#define BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_H

#include "payments_defs.h"
#include "payment_type.h"

namespace Payments {

class PaymentSystem {
public:
    virtual ~PaymentSystem() = default;

    virtual void pay(unsigned int amount, PaymentType paymentType, const std::string& paymentData,
                           PaymentCallback callback) = 0;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_H
