//
// Created by TriD on 15.02.2022.
//

#include "pay_on_ticket_machine_strategy.h"

#include "../../gates/public/gates_controller.h"

namespace Parking {

PayOnTicketMachineStrategy::PayOnTicketMachineStrategy(CarRegistry& carsRegistry,
                                                       Gates::GatesController& gateController)
                                                       : _carsRegistry(carsRegistry),
                                                       _gateController(gateController) {}

void PayOnTicketMachineStrategy::onCarEntering(std::size_t gateId, const std::string& carId) {
    _carsRegistry.addCar(carId);
    _gateController.releaseGate(gateId);
}

void PayOnTicketMachineStrategy::onCarLeaving(std::size_t gateId, const std::string& carId) {
    auto carIter = _payedCars.find(carId);
    if (carIter != _payedCars.end()) {
        _payedCars.erase(carIter);
        _gateController.releaseGate(gateId);
    } else {
        // Ensure gate is closed
        _gateController.closeGate(gateId);
    }
}

void PayOnTicketMachineStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::PaymentResult::Accepted) {
        // TODO: Log payment error
        return;
    }
    _payedCars.insert(carId);
}

} // namespace Parking