//
// Created by TriD on 05.02.2022.
//

#include "simple_payment_system.h"

#include "cash_payement_provider.h"
#include "card_payment_provider.h"

namespace Payments {

Payments::SimplePaymentSystem::SimplePaymentSystem(std::unique_ptr<CashPaymentProvider> cashPaymentProvider,
                                                   std::unique_ptr<CardPaymentProvider> cardPaymentProvider)
        : _cashPaymentProvider(std::move(cashPaymentProvider)), _cardPaymentProvider(std::move(cardPaymentProvider)) {}


void Payments::SimplePaymentSystem::pay(unsigned int amount, PaymentType paymentType, const std::string& paymentData, Payments::PaymentCallback callback) {
    switch (paymentType) {
        case Cash:
            _cashPaymentProvider->pay(amount, callback);
            break;
        case CashCard:
            _cardPaymentProvider->pay(amount, paymentData, callback);
            break;
        case SubscriptionCard:
            // TODO: Integrate subscriptions here
            callback(PaymentResult::Error);
            break;
    }
}

} // namespace Payments