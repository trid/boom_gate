//
// Created by TriD on 05.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../private/cash_payement_provider.h"
#include "../private/card_payment_provider.h"
#include "../private/simple_payment_system.h"
#include "../private/subscription_card_payment_provider.h"

namespace Payments::Tests {

using namespace testing;

class CashPaymentProviderMock : public CashPaymentProvider {
public:
    MOCK_METHOD(void, pay, (unsigned int, PaymentCallback), (override));
};

class CardPaymentProviderMock : public CardPaymentProvider {
public:
    MOCK_METHOD(void, pay, (unsigned int, const std::string&, PaymentCallback), (override));
};

class SubscriptionCardPaymentProviderMock : public SubscriptionCardPaymentProvider {
public:
    MOCK_METHOD(void, pay, (const std::string&, PaymentCallback), (override));
};

TEST(PrintingCardPaymentProviderTestSuite, paymentInCash) {
    auto cashPaymentProvider = std::make_unique<CashPaymentProviderMock>();
    auto& cashPaymentProviderRef = *cashPaymentProvider;
    auto cardPaymentProvider = std::make_unique<CardPaymentProviderMock>();

    EXPECT_CALL(cashPaymentProviderRef, pay).WillOnce(Return());

    SimplePaymentSystem paymentSystem(std::move(cashPaymentProvider), std::move(cardPaymentProvider), nullptr);

    paymentSystem.pay(PaymentType::Cash, 100, "", [](PaymentResult) {});
}

TEST(PrintingCardPaymentProviderTestSuite, paymentWithCard) {
    auto cashPaymentProvider = std::make_unique<CashPaymentProviderMock>();
    auto cardPaymentProvider = std::make_unique<CardPaymentProviderMock>();
    auto& cardPaymentProviderRef = *cardPaymentProvider;

    EXPECT_CALL(cardPaymentProviderRef, pay).WillOnce(Return());

    SimplePaymentSystem paymentSystem(std::move(cashPaymentProvider), std::move(cardPaymentProvider), nullptr);

    paymentSystem.pay(PaymentType::CashCard, 100, "FOO", [](PaymentResult) {});
}

TEST(PrintingCardPaymentProviderTestSuite, paymentWithSubscribtionCard) {
    auto cashPaymentProvider = std::make_unique<CashPaymentProviderMock>();
    auto cardPaymentProvider = std::make_unique<CardPaymentProviderMock>();
    auto subscriptionCardPaymentProvider = std::make_unique<SubscriptionCardPaymentProviderMock>();

    EXPECT_CALL(*subscriptionCardPaymentProvider, pay);

    SimplePaymentSystem paymentSystem(std::move(cashPaymentProvider), std::move(cardPaymentProvider),
                                      std::move(subscriptionCardPaymentProvider));

    paymentSystem.pay(PaymentType::SubscriptionCard, 0, "FOO", [](PaymentResult) {});
}

} // namespace Payments::Tests