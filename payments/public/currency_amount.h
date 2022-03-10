//
// Created by TriD on 23.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_CURRENCY_AMOUNT_H
#define BOOM_GATE_APPLICATION_CURRENCY_AMOUNT_H

#include <string>

namespace Payments {

struct CurrencyAmount {
    unsigned int amount = 0;
    std::string isoCurrency;

    bool operator==(const CurrencyAmount& other) const {
        return other.amount == amount && other.isoCurrency == isoCurrency;
    }
};

} // namespace Payments

#endif //BOOM_GATE_APPLICATION_CURRENCY_AMOUNT_H
