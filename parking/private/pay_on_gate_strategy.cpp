//
// Created by TriD on 14.02.2022.
//

#include "pay_on_gate_strategy.h"

#include "../../gates/public/gate.h"

namespace Parking {

PayOnGateStrategy::PayOnGateStrategy(Billing::BillingSystem& billingSystem, CarRegistry& carsRegistry,
                                     Billing::BillingInformationListener& billingListener) :
        _carsRegistry(carsRegistry),
        _billingSystem(billingSystem),
        _billingListener(billingListener) {}

void PayOnGateStrategy::onCarEntering(std::size_t gateId, const std::string& carId) {
    _carsRegistry.addCar(carId);

    GateControllerBase::releaseGate(gateId);
}

void PayOnGateStrategy::onCarLeaving(std::size_t gateId, const std::string& carId) {
    // Ensure gate is closed
    GateControllerBase::closeGate(gateId);

    _carToGateId[carId] = gateId;
    auto billingAmount = _billingSystem.getBill(carId);
    _billingListener.onBillingInformationProduced(carId, billingAmount);
}

void PayOnGateStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::Accepted) {
        // TODO Log payment errors
        return;
    }

    auto gateId = _carToGateId[carId];
    _carsRegistry.removeCar(carId);
    _carToGateId.erase(carId);
    GateControllerBase::releaseGate(gateId);
}

void PayOnGateStrategy::addGate(Gates::GateUPtr gate) {
    GateControllerBase::addGate(std::move(gate));
}

} // namespace Parking
