//
// Created by TriD on 14.02.2022.
//

#include "pay_on_gate_strategy.h"

#include "../public/billing_information_listener.h"

#include "../../billing/public/billing_system.h"
#include "../../gates/public/gate.h"

namespace Parking {

PayOnGateStrategy::PayOnGateStrategy(Billing::BillingSystem& billingSystem,
                                     std::unordered_map<std::string, unsigned int>& carsRegistry,
                                     BillingInformationListener& billingListener) : _carsRegistry(
        carsRegistry), _billingSystem(billingSystem), _billingListener(billingListener) {}

void PayOnGateStrategy::onCarEntering(std::size_t gateId, const std::string& carId, unsigned int tickId) {
    checkGateValid(gateId);

    _carsRegistry[carId] = tickId;

    releaseGate(gateId);
}

void PayOnGateStrategy::onCarLeaving(std::size_t gateId, const std::string& carId, unsigned int tickId) {
    checkGateValid(gateId);

    std::unique_ptr<Gates::Gate>& gate = _gates[gateId];
    // Ensure gate is closed
    gate->close();

    _carToGateId[carId] = gateId;
    auto billingAmount = _billingSystem.getBill(carId, tickId);
    _billingListener.billedFor(gateId, billingAmount);
}

void PayOnGateStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::Accepted) {
        // TODO Log payment errors
        return;
    }

    auto gateId = _carToGateId[carId];
    _carsRegistry.erase(carId);
    _carToGateId.erase(carId);
    releaseGate(gateId);
}

void PayOnGateStrategy::addGate(std::unique_ptr<Gates::Gate> gate) {
    _gates.push_back(std::move(gate));
}

bool PayOnGateStrategy::checkGateValid(std::size_t gateId) {
    if (gateId >= _gates.size()) {
        // TODO Log error here
        return false;
    }
    return true;
}

void PayOnGateStrategy::releaseGate(size_t gateId) {
    std::unique_ptr<Gates::Gate>& gate = _gates[gateId];
    gate->open();
    // TODO wait for car to drive through
    gate->close();
}

} // namespace Parking
