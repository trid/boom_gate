//
// Created by TriD on 04.02.2022.
//

#include "printing_card_payment_provider.h"
#include "../public/currency_amount.h"


namespace Payments {

PrintingCardPaymentProvider::PrintingCardPaymentProvider(std::ostream& output) : _output(output) {}

void PrintingCardPaymentProvider::pay(const CurrencyAmount& amount, const std::string& cardNumber, PaymentCallback callback) {
    _output << "Payed " << amount.amount << " " << amount.isoCurrency << " from " << cardNumber << std::endl;
    callback(PaymentResult::Accepted);
}

} // namespace Payments