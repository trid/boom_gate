//
// Created by TriD on 15.02.2022.
//

#include "pay_on_ticket_machine_strategy.h"

#include "../../gates/public/gate.h"


namespace Parking {

PayOnTicketMachineStrategy::PayOnTicketMachineStrategy(CarRegistry& carsRegistry)
                                                       : _carsRegistry(carsRegistry) {}

void PayOnTicketMachineStrategy::onCarEntering(std::size_t gateId, const boost::uuids::uuid& accountId) {
    _carsRegistry.addCar(accountId);
    GateControllerBase::releaseGate(gateId);
}

void PayOnTicketMachineStrategy::onCarLeaving(std::size_t gateId, const boost::uuids::uuid& accountId) {
    auto carIter = _payedCars.find(accountId);
    if (carIter != _payedCars.end()) {
        _payedCars.erase(carIter);
        GateControllerBase::releaseGate(gateId);
    } else {
        // Ensure gate is closed
        GateControllerBase::closeGate(gateId);
    }
}

void PayOnTicketMachineStrategy::onPayment(const boost::uuids::uuid& accountId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::PaymentResult::Accepted) {
        // TODO: Log payment error
        return;
    }
    _payedCars.insert(accountId);
}

void PayOnTicketMachineStrategy::addGate(Gates::GateUPtr gate) {
    GateControllerBase::addGate(std::move(gate));
}

} // namespace Parking