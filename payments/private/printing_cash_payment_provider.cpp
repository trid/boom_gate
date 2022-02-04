//
// Created by TriD on 04.02.2022.
//

#include "printing_cash_payment_provider_test_suite.h"

namespace Payments {

PrintingCashPaymentProvider::PrintingCashPaymentProvider(std::ostream& ostream) : _output(ostream) {}

void PrintingCashPaymentProvider::pay(unsigned int amount, PaymentCallback callback) {
    _output << "Payed $" << amount << " in cash" << std::endl;
    callback(PaymentResult::Accepted);
}


} // namespace Payments