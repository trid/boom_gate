//
// Created by TriD on 16.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PRINTING_SUBSCRIPTION_PAYMENT_PROVIDER_H
#define BOOM_GATE_APPLICATION_PRINTING_SUBSCRIPTION_PAYMENT_PROVIDER_H

#include <iostream>

#include "subscription_card_payment_provider.h"

namespace Payments {

class PrintingSubscriptionPaymentProvider: public SubscriptionCardPaymentProvider{
public:
    PrintingSubscriptionPaymentProvider(std::ostream& ostream);

    void pay(const std::string& cardId, PaymentCallback callback) override;

private:
    std::ostream& ostream;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PRINTING_SUBSCRIPTION_PAYMENT_PROVIDER_H
