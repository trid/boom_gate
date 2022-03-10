//
// Created by TriD on 04.02.2022.
//

#include "printing_cash_payment_provider.h"

namespace Payments {

PrintingCashPaymentProvider::PrintingCashPaymentProvider(std::ostream& ostream) : _output(ostream) {}

void PrintingCashPaymentProvider::pay(const CurrencyAmount& amount, PaymentCallback callback) {
    _output << "Payed " << amount.amount << " " << amount.isoCurrency << " in cash" << std::endl;
    callback(PaymentResult::Accepted);
}


} // namespace Payments