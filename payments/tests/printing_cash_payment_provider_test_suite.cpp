//
// Created by TriD on 04.02.2022.
//

#include "gtest/gtest.h"

#include <sstream>

#include "../private/printing_cash_payment_provider_test_suite.h"

namespace Payments::Tests {

TEST(PrintingCashPaymentProviderTestSuite, paymentAccepted) {
    std::stringstream ss;
    PrintingCashPaymentProvider paymentProvider(ss);

    PaymentResult result;
    paymentProvider.pay(100, [&result](PaymentResult callbackResult){
        result = callbackResult;
    });

    ASSERT_EQ(PaymentResult::Accepted, result);
    ASSERT_EQ("Payed $100 in cash\n", ss.str());
}

} // namespace Payments::Tests
