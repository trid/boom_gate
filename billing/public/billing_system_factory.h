//
// Created by TriD on 14.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_BILLING_SYSTEM_FACTORY_H
#define BOOM_GATE_APPLICATION_BILLING_SYSTEM_FACTORY_H

#include <memory>
#include <unordered_map>
#include "../../shared/public/timer.h"

namespace Billing {

class BillingSystem;

class BillingSystemFactory {
public:
    static std::unique_ptr<BillingSystem>
    create(const Utils::Timer& timer, const std::unordered_map<std::string, unsigned int>& registry);
};

} // namespace Billing

#endif //BOOM_GATE_APPLICATION_BILLING_SYSTEM_FACTORY_H
