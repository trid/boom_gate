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


void Payments::SimplePaymentSystem::pay_cash(unsigned int amount, Payments::PaymentCallback callback) {
    _cashPaymentProvider->pay(amount, callback);
}

void Payments::SimplePaymentSystem::pay_card(Payments::CardPaymentData&& cardPaymentData,
                                             Payments::PaymentCallback callback) {
    _cardPaymentProvider->pay(std::move(cardPaymentData), callback);
}

} // namespace Payments