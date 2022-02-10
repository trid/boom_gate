//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_FACTORY_H
#define BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_FACTORY_H

#include <memory>

namespace Payments {

class PaymentSystem;

class PaymentSystemFactory {
public:
    static std::unique_ptr<PaymentSystem> create();
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PAYMENT_SYSTEM_FACTORY_H
