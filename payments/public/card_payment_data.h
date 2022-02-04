//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PAYMENT_DATA_H
#define BOOM_GATE_APPLICATION_PAYMENT_DATA_H

#include <string>

namespace Payments {

struct CardPaymentData {
    unsigned int amount;
    std::string cardData;
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_PAYMENT_DATA_H
