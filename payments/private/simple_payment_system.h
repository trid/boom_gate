//
// Created by TriD on 05.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_SIMPLE_PAYMENT_SYSTEM_H
#define BOOM_GATE_APPLICATION_SIMPLE_PAYMENT_SYSTEM_H

#include <memory>

#include "../public/payment_system.h"
#include "../public/currency_amount.h"

namespace Payments {

class CashPaymentProvider;
class CardPaymentProvider;
class SubscriptionCardPaymentProvider;

class SimplePaymentSystem : public PaymentSystem {
public:
    SimplePaymentSystem(std::unique_ptr<CashPaymentProvider> cashPaymentProvider,
                        std::unique_ptr<CardPaymentProvider> cardPaymentProvider,
                        std::unique_ptr<SubscriptionCardPaymentProvider> subscriptionCardPaymentProvider);

    void
    pay(PaymentType paymentType, const Payments::CurrencyAmount& amount, const std::string& paymentData, PaymentCallback callback) override;

private:
    std::unique_ptr<CashPaymentProvider> _cashPaymentProvider;
    std::unique_ptr<CardPaymentProvider> _cardPaymentProvider;
    std::unique_ptr<SubscriptionCardPaymentProvider> _subscriptionCardPaymentProvider;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_SIMPLE_PAYMENT_SYSTEM_H
