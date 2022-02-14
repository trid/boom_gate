//
// Created by TriD on 15.02.2022.
//

#include "pay_on_parkomate_strategy.h"

#include "../../gates/public/gate.h"

namespace Parking {

PayOnParkomateStrategy::PayOnParkomateStrategy(std::unordered_map<std::string, unsigned int>& carsRegistry,
                                               Billing::BillingSystem& billingSystem,
                                               BillingInformationListener& billingListener) : _carsRegistry(
        carsRegistry), _billingSystem(billingSystem), _billingListener(billingListener) {}

void PayOnParkomateStrategy::onCarEntering(std::size_t gateId, const std::string& carId, unsigned int tickId) {
    _carsRegistry[carId] = tickId;
}

void PayOnParkomateStrategy::onCarLeaving(std::size_t gateId, const std::string& carId, unsigned int tickId) {
    auto carIter = _payedCars.find(carId);
    if (carIter != _payedCars.end()) {
        _payedCars.erase(carIter);
        checkGateValid(gateId);
        releaseGate(gateId);
    }
}

void PayOnParkomateStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::PaymentResult::Accepted) {
        // TODO: Log payment error
        return;
    }
    _payedCars.insert(carId);
}

void PayOnParkomateStrategy::addGate(std::unique_ptr<Gates::Gate> gate) {
    _gates.push_back(std::move(gate));
}

void PayOnParkomateStrategy::checkGateValid(size_t gateId) {
    if (gateId >= _gates.size()) {
        // TODO Log error here
    }
}

void PayOnParkomateStrategy::releaseGate(size_t gateId) {
    std::unique_ptr<Gates::Gate>& gate = _gates[gateId];
    gate->open();
    // TODO wait for car to drive through
    gate->close();
}
} // namespace Parking