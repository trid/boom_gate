//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_H
#define BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_H

#include "card_payment_data.h"
#include "payments_defs.h"

namespace Payments {

class PaymentSystem {
public:
    virtual ~PaymentSystem() = default;

    virtual void payInCash(unsigned int amount, PaymentCallback callback) = 0;
    virtual void payWithCard(CardPaymentData&& cardPaymentData, PaymentCallback callback) = 0;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_H
