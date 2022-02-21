//
// Created by TriD on 16.02.2022.
//

#include "printing_subscription_payment_provider.h"

namespace Payments {

Payments::PrintingSubscriptionPaymentProvider::PrintingSubscriptionPaymentProvider(std::ostream& ostream) : ostream(
        ostream) {}

void PrintingSubscriptionPaymentProvider::pay(const std::string& cardId, PaymentCallback callback) {
    ostream << "Payed with subscription card " << cardId << std::endl;
    callback(PaymentResult::Accepted);
}

} // namespace Payments