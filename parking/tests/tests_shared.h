//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_TESTS_SHARED_H
#define BOOM_GATE_APPLICATION_TESTS_SHARED_H

#include "../../billing/public/billing_information_listener.h"
#include "../../billing/public/billing_system.h"

namespace Parking::Test {

class BillingSystemMock : public Billing::BillingSystem {
public:
    MOCK_METHOD(unsigned int, getBill, (const std::string&), (override));
};

class BillingListenerMock : public Billing::BillingInformationListener {
public:
    BillingListenerMock() {
        ON_CALL(*this, onBillingInformationProduced).WillByDefault(
                [this](const std::string&, unsigned int amount) {
                    _billedAmount = amount;
                });
    }

    unsigned int getBilledAmount() const {
        return _billedAmount;
    }

    MOCK_METHOD(void, onBillingInformationProduced, (const std::string&, unsigned int), (override));
private:
    unsigned int _billedAmount = 0;
};

} // namespace Parking::Test

#endif //BOOM_GATE_APPLICATION_TESTS_SHARED_H
