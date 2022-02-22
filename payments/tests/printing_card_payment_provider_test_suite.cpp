//
// Created by TriD on 04.02.2022.
//

#include "gtest/gtest.h"

#include <sstream>

#include "../private/printing_card_payment_provider.h"

namespace Payments::Tests {

TEST(PrintingCardPaymentProviderTestSuite, paymentAccepted) {
    std::stringstream ss;
    PrintingCardPaymentProvider paymentProvider(ss);

    PaymentResult result;
    paymentProvider.pay({100, "USD"}, "1234432112344321", [&result](PaymentResult callbackResult){
        result = callbackResult;
    });

    ASSERT_EQ(PaymentResult::Accepted, result);
    ASSERT_EQ("Payed $100 from 1234432112344321\n", ss.str());
}

} // namespace Payments::Tests