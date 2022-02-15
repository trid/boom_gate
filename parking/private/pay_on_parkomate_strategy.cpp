//
// Created by TriD on 15.02.2022.
//

#include "pay_on_parkomate_strategy.h"

#include "../../gates/public/gates_controller.h"

namespace Parking {

PayOnParkomateStrategy::PayOnParkomateStrategy(Billing::BillingSystem& billingSystem,
                                               std::unordered_map<std::string, unsigned int>& carsRegistry,
                                               BillingInformationListener& billingListener,
                                               Gates::GatesController& gateController) : _carsRegistry(
        carsRegistry), _billingSystem(billingSystem), _billingListener(billingListener), _gateController(gateController) {}

void PayOnParkomateStrategy::onCarEntering(std::size_t gateId, const std::string& carId, unsigned int tickId) {
    _carsRegistry[carId] = tickId;
}

void PayOnParkomateStrategy::onCarLeaving(std::size_t gateId, const std::string& carId, unsigned int tickId) {
    auto carIter = _payedCars.find(carId);
    if (carIter != _payedCars.end()) {
        _payedCars.erase(carIter);
        _gateController.releaseGate(gateId);
    }
}

void PayOnParkomateStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::PaymentResult::Accepted) {
        // TODO: Log payment error
        return;
    }
    _payedCars.insert(carId);
}

} // namespace Parking