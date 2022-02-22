//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CASH_PAYEMENT_PROVIDER_H
#define BOOM_GATE_APPLICATION_CASH_PAYEMENT_PROVIDER_H

#include "../public/payments_defs.h"
#include "../public/currency_amount.h"

namespace Payments {

class CashPaymentProvider {
public:
    virtual ~CashPaymentProvider() = default;

    virtual void pay(const CurrencyAmount& amount, PaymentCallback callback) = 0;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_CASH_PAYEMENT_PROVIDER_H
