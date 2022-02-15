//
// Created by TriD on 05.02.2022.
//

#include "simple_payment_system.h"

#include "cash_payement_provider.h"
#include "card_payment_provider.h"
#include "subscription_card_payment_provider.h"

namespace Payments {

Payments::SimplePaymentSystem::SimplePaymentSystem(std::unique_ptr<CashPaymentProvider> cashPaymentProvider,
                                                   std::unique_ptr<CardPaymentProvider> cardPaymentProvider,
                                                   std::unique_ptr<SubscriptionCardPaymentProvider> subscriptionCardPaymentProvider)
        : _cashPaymentProvider(std::move(cashPaymentProvider)),
        _cardPaymentProvider(std::move(cardPaymentProvider)),
        _subscriptionCardPaymentProvider(std::move(subscriptionCardPaymentProvider)) {}


void Payments::SimplePaymentSystem::pay(PaymentType paymentType, unsigned int amount, const std::string& paymentData,
                                        PaymentCallback callback) {
    switch (paymentType) {
        case Cash:
            _cashPaymentProvider->pay(amount, callback);
            break;
        case CashCard:
            _cardPaymentProvider->pay(amount, paymentData, callback);
            break;
        case SubscriptionCard:
            _subscriptionCardPaymentProvider->pay(paymentData, callback);
            break;
    }
}

} // namespace Payments