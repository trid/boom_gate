//
// Created by TriD on 08.02.2022.
//

#include "../public/payment_system_factory.h"

#include "simple_payment_system.h"
#include "printing_card_payment_provider.h"
#include "printing_cash_payment_provider_test_suite.h"
#include "printing_subscription_payment_provider.h"

namespace Payments {

// static
std::unique_ptr<PaymentSystem> PaymentSystemFactory::create() {
    return std::make_unique<SimplePaymentSystem>(std::make_unique<PrintingCashPaymentProvider>(std::cout),
                                                 std::make_unique<PrintingCardPaymentProvider>(std::cout),
                                                         std::make_unique<PrintingSubscriptionPaymentProvider>(std::cout));
}
} // namespace Payments