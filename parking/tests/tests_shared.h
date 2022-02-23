//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_TESTS_SHARED_H
#define BOOM_GATE_APPLICATION_TESTS_SHARED_H

#include <boost/uuid/uuid.hpp>
#include "../../billing/public/billing_information_listener.h"
#include "../../billing/public/billing_system.h"

namespace Parking::Test {

class BillingSystemMock : public Billing::BillingSystem {
public:
    MOCK_METHOD(Payments::CurrencyAmount, getBill, (const boost::uuids::uuid&), (override));
};

class BillingListenerMock : public Billing::BillingInformationListener {
public:
    BillingListenerMock() {
        ON_CALL(*this, onBillingInformationProduced).WillByDefault(
                [this](const boost::uuids::uuid&, const Payments::CurrencyAmount& amount) {
                    _billedAmount = amount;
                });
    }

    const Payments::CurrencyAmount& getBilledAmount() const {
        return _billedAmount;
    }

    MOCK_METHOD(void, onBillingInformationProduced, (const boost::uuids::uuid&, const Payments::CurrencyAmount&), (override));
private:
    Payments::CurrencyAmount _billedAmount{0, ""};
};

} // namespace Parking::Test

#endif //BOOM_GATE_APPLICATION_TESTS_SHARED_H
