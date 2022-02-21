//
// Created by TriD on 14.02.2022.
//

#include "gtest/gtest.h"

#include "../private/ticks_based_billing_system.h"

namespace Billing::Tests {

TEST(TicksBasedBillingSystemTestSuite, billCarForSpentTime) {
    std::unordered_map<std::string, unsigned int> registry;
    constexpr char carId[] = "ab123c";
    registry.emplace(carId, 0);

    TicksBasedBillingSystem billingSystem{registry};
    auto billedAmount = billingSystem.getBill(carId, 5);

    ASSERT_EQ(50, billedAmount);
}

} // namespace Billing::Tests