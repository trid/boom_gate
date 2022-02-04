//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CARD_PAYMENT_PROVIDER_H
#define BOOM_GATE_APPLICATION_CARD_PAYMENT_PROVIDER_H

#include "../public/card_payment_data.h"
#include "../public/payments_defs.h"

namespace Payments {

class CardPaymentProvider {
public:
    virtual ~CardPaymentProvider() = default;

    virtual void pay(CardPaymentData&& cardPaymentData, PaymentCallback callback) = 0;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_CARD_PAYMENT_PROVIDER_H
