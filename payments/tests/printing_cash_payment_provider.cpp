//
// Created by TriD on 04.02.2022.
//

#include "gtest/gtest.h"

#include <sstream>

#include "../private/printing_cash_payment_provider.h"

namespace Payments::Tests {

TEST(PrintingCashPaymentProviderTestSuite, paymentAccepted) {
    std::stringstream ss;
    PrintingCashPaymentProvider paymentProvider(ss);

    PaymentResult result;
    paymentProvider.pay({100, "USD"}, [&result](PaymentResult callbackResult){
        result = callbackResult;
    });

    ASSERT_EQ(PaymentResult::Accepted, result);
    ASSERT_EQ("Payed 100 USD in cash\n", ss.str());
}

} // namespace Payments::Tests
