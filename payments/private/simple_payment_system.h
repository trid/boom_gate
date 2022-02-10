//
// Created by TriD on 05.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_SIMPLE_PAYMENT_SYSTEM_H
#define BOOM_GATE_APPLICATION_SIMPLE_PAYMENT_SYSTEM_H

#include <memory>

#include "../public/payment_system.h"

namespace Payments {

class CashPaymentProvider;

class CardPaymentProvider;

class SimplePaymentSystem : public PaymentSystem {
public:
    SimplePaymentSystem(std::unique_ptr<CashPaymentProvider> cashPaymentProvider,
                        std::unique_ptr<CardPaymentProvider> cardPaymentProvider);

    void pay(unsigned int amount, PaymentType paymentType, const std::string& paymentData,
             PaymentCallback callback) override;

private:
    std::unique_ptr<CashPaymentProvider> _cashPaymentProvider;
    std::unique_ptr<CardPaymentProvider> _cardPaymentProvider;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_SIMPLE_PAYMENT_SYSTEM_H
