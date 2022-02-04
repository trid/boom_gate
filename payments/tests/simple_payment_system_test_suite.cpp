//
// Created by TriD on 05.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../private/cash_payement_provider.h"
#include "../private/card_payment_provider.h"
#include "../private/simple_payment_system.h"

namespace Payments::Tests {

using namespace testing;

class CashPaymentProviderMock: public CashPaymentProvider{
public:
    MOCK_METHOD(void, pay, (unsigned int, PaymentCallback), (override));
};

class CardPaymentProviderMock: public CardPaymentProvider{
public:
    MOCK_METHOD(void, pay, (CardPaymentData&&, PaymentCallback), (override));
};

TEST(PrintingCardPaymentProviderTestSuite, paymentInCash) {
    auto cashPaymentProvider = std::make_unique<CashPaymentProviderMock>();
    auto& cashPaymentProviderRef = *cashPaymentProvider;
    auto cardPaymentProvider = std::make_unique<CardPaymentProviderMock>();

    EXPECT_CALL(cashPaymentProviderRef, pay).WillOnce(Return());

    SimplePaymentSystem paymentSystem(std::move(cashPaymentProvider), std::move(cardPaymentProvider));

    paymentSystem.pay_cash(100, [](PaymentResult){});
}

TEST(PrintingCardPaymentProviderTestSuite, paymentWithCard) {
    auto cashPaymentProvider = std::make_unique<CashPaymentProviderMock>();
    auto cardPaymentProvider = std::make_unique<CardPaymentProviderMock>();
    auto& cardPaymentProviderRef = *cardPaymentProvider;

    EXPECT_CALL(cardPaymentProviderRef, pay).WillOnce(Return());

    SimplePaymentSystem paymentSystem(std::move(cashPaymentProvider), std::move(cardPaymentProvider));

    paymentSystem.pay_card({100, "FOO"}, [](PaymentResult){});
}

} // namespace Payments::Tests