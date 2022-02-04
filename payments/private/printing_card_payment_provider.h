//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PRINTING_CARD_PAYMENT_PROVIDER_H
#define BOOM_GATE_APPLICATION_PRINTING_CARD_PAYMENT_PROVIDER_H

#include <iostream>

#include "card_payment_provider.h"

namespace Payments {

class PrintingCardPaymentProvider : public CardPaymentProvider {
public:
    explicit PrintingCardPaymentProvider(std::ostream& output);

    void pay(CardPaymentData&& cardPaymentData, PaymentCallback callback) override;

private:
    std::ostream& _output;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PRINTING_CARD_PAYMENT_PROVIDER_H
