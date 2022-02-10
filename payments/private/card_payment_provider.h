//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CARD_PAYMENT_PROVIDER_H
#define BOOM_GATE_APPLICATION_CARD_PAYMENT_PROVIDER_H

#include "../public/payments_defs.h"

namespace Payments {

class CardPaymentProvider {
public:
    virtual ~CardPaymentProvider() = default;

    virtual void pay(unsigned int amount, const std::string& cardNumber, PaymentCallback callback) = 0;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_CARD_PAYMENT_PROVIDER_H
