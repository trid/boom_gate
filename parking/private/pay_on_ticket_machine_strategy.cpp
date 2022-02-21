//
// Created by TriD on 15.02.2022.
//

#include "pay_on_ticket_machine_strategy.h"

#include "../../gates/public/gate.h"


namespace Parking {

PayOnTicketMachineStrategy::PayOnTicketMachineStrategy(CarRegistry& carsRegistry)
                                                       : _carsRegistry(carsRegistry) {}

void PayOnTicketMachineStrategy::onCarEntering(std::size_t gateId, const std::string& carId) {
    _carsRegistry.addCar(carId);
    GateControllerBase::releaseGate(gateId);
}

void PayOnTicketMachineStrategy::onCarLeaving(std::size_t gateId, const std::string& carId) {
    auto carIter = _payedCars.find(carId);
    if (carIter != _payedCars.end()) {
        _payedCars.erase(carIter);
        GateControllerBase::releaseGate(gateId);
    } else {
        // Ensure gate is closed
        GateControllerBase::closeGate(gateId);
    }
}

void PayOnTicketMachineStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::PaymentResult::Accepted) {
        // TODO: Log payment error
        return;
    }
    _payedCars.insert(carId);
}

void PayOnTicketMachineStrategy::addGate(Gates::GateUPtr gate) {
    GateControllerBase::addGate(std::move(gate));
}

} // namespace Parking