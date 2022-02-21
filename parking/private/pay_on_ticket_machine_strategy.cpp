//
// Created by TriD on 15.02.2022.
//

#include "pay_on_ticket_machine_strategy.h"

#include "../../gates/public/gates_controller.h"
#include "../../shared/public/timer.h"

namespace Parking {

PayOnTicketMachineStrategy::PayOnTicketMachineStrategy(Billing::BillingSystem& billingSystem,
                                                       std::unordered_map<std::string, unsigned int>& carsRegistry,
                                                       Billing::BillingInformationListener& billingListener,
                                                       Gates::GatesController& gateController,
                                                       const Utils::Timer& timer)
                                                       : _carsRegistry(carsRegistry),
                                                       _billingSystem(billingSystem),
                                                       _billingListener(billingListener),
                                                       _gateController(gateController),
                                                       _timer(timer) {}

void PayOnTicketMachineStrategy::onCarEntering(std::size_t gateId, const std::string& carId) {
    _carsRegistry[carId] = _timer.getTicks();
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