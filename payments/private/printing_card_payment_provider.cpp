//
// Created by TriD on 04.02.2022.
//

#include "printing_card_payment_provider.h"


namespace Payments {

PrintingCardPaymentProvider::PrintingCardPaymentProvider(std::ostream& output) : _output(output) {}

void PrintingCardPaymentProvider::pay(CardPaymentData&& cardPaymentData, PaymentCallback callback) {
    _output << "Payed $" << cardPaymentData.amount << " from " << cardPaymentData.cardData << std::endl;
    callback(PaymentResult::Accepted);
}

} // namespace Payments