//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PRINTING_CASH_PAYMENT_PROVIDER_H
#define BOOM_GATE_APPLICATION_PRINTING_CASH_PAYMENT_PROVIDER_H

#include "cash_payement_provider.h"
#include "../public/currency_amount.h"

#include <iostream>

namespace Payments {

class PrintingCashPaymentProvider: public CashPaymentProvider {
public:
    explicit PrintingCashPaymentProvider(std::ostream& ostream);

    void pay(const CurrencyAmount& amount, PaymentCallback callback) override;

private:
    std::ostream& _output;
};

}

#endif //BOOM_GATE_APPLICATION_PRINTING_CASH_PAYMENT_PROVIDER_H
