//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAYMENTS_DEFS_H
#define BOOM_GATE_APPLICATION_PAYMENTS_DEFS_H

#include "functional"

#include "payment_result.h"

namespace Payments {

using PaymentCallback = std::function<void(PaymentResult)>;

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PAYMENTS_DEFS_H
