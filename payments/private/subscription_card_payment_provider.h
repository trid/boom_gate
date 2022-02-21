//
// Created by TriD on 16.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_SUBSCRIBTION_CARD_PROVIDER_H
#define BOOM_GATE_APPLICATION_SUBSCRIBTION_CARD_PROVIDER_H

#include <string>

#include "../public/payments_defs.h"

namespace Payments {

class SubscriptionCardPaymentProvider {
public:
    virtual ~SubscriptionCardPaymentProvider() = default;

    virtual void pay(const std::string& cardId, PaymentCallback callback) = 0;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_SUBSCRIBTION_CARD_PROVIDER_H
