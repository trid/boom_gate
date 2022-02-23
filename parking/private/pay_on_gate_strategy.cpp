//
// Created by TriD on 14.02.2022.
//

#include "pay_on_gate_strategy.h"

#include "../public/parking_error_listener.h"

#include "../../gates/public/gate.h"

namespace Parking {

PayOnGateStrategy::PayOnGateStrategy(Billing::BillingSystem& billingSystem, CarRegistry& carsRegistry,
                                     Billing::BillingInformationListener& billingListener,
                                     ParkingErrorListener& parkingErrorListener) :
        _carsRegistry(carsRegistry),
        _billingSystem(billingSystem),
        _billingListener(billingListener),
        _parkingErrorListener(parkingErrorListener) {}

void PayOnGateStrategy::onCarEntering(std::size_t gateId, const boost::uuids::uuid& accountId) {
    if (_carsRegistry.hasAvailableParkingLots()) {
        _carsRegistry.addCar(accountId);

        GateControllerBase::releaseGate(gateId);
    }
    else {
        _parkingErrorListener.onError("Parking is full");
    }
}

void PayOnGateStrategy::onCarLeaving(std::size_t gateId, const boost::uuids::uuid& accountId) {
    // Ensure gate is closed
    GateControllerBase::closeGate(gateId);

    _carToGateId[accountId] = gateId;
    auto billingAmount = _billingSystem.getBill(accountId);
    _billingListener.onBillingInformationProduced(accountId, billingAmount);
}

void PayOnGateStrategy::onPayment(const boost::uuids::uuid& accountId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::Accepted) {
        // TODO Log payment errors
        return;
    }

    auto gateId = _carToGateId[accountId];
    _carsRegistry.removeCar(accountId);
    _carToGateId.erase(accountId);
    GateControllerBase::releaseGate(gateId);
}

void PayOnGateStrategy::addGate(Gates::GateUPtr gate) {
    GateControllerBase::addGate(std::move(gate));
}

} // namespace Parking
