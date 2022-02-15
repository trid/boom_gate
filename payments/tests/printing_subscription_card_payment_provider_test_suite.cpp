//
// Created by TriD on 16.02.2022.
//

#include "gtest/gtest.h"

#include <sstream>

#include "../private/printing_subscription_payment_provider.h"

namespace Payments::Tests {

TEST(PrintingSubscriptionCardPaymentProviderTestSuite, paymentAccepted) {
    std::stringstream ss;
    PrintingSubscriptionPaymentProvider paymentProvider(ss);

    PaymentResult result;
    paymentProvider.pay("100", [&result](PaymentResult callbackResult){
        result = callbackResult;
    });

    ASSERT_EQ(PaymentResult::Accepted, result);
    ASSERT_EQ("Payed with subscription card 100\n", ss.str());
}

} // namespace Payments::Tests