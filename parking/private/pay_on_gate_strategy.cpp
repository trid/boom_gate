//
// Created by TriD on 14.02.2022.
//

#include "pay_on_gate_strategy.h"

#include "../../billing/public/billing_information_listener.h"

#include "../../billing/public/billing_system.h"
#include "../../gates/public/gates_controller.h"
#include "../public/car_registry.h"

namespace Parking {

PayOnGateStrategy::PayOnGateStrategy(Billing::BillingSystem& billingSystem, CarRegistry& carsRegistry,
                                     Billing::BillingInformationListener& billingListener,
                                     Gates::GatesController& gateController) :
        _carsRegistry(carsRegistry),
        _billingSystem(billingSystem),
        _billingListener(billingListener),
        _gateController(gateController) {}

void PayOnGateStrategy::onCarEntering(std::size_t gateId, const std::string& carId) {
    _carsRegistry.addCar(carId);

    _gateController.releaseGate(gateId);
}

void PayOnGateStrategy::onCarLeaving(std::size_t gateId, const std::string& carId) {
    // Ensure gate is closed
    _gateController.closeGate(gateId);

    _carToGateId[carId] = gateId;
    auto billingAmount = _billingSystem.getBill(carId);
    _billingListener.billedFor(gateId, billingAmount);
}

void PayOnGateStrategy::onPayment(const std::string& carId, Payments::PaymentResult paymentResult) {
    if (paymentResult != Payments::Accepted) {
        // TODO Log payment errors
        return;
    }

    auto gateId = _carToGateId[carId];
    _carsRegistry.removeCar(carId);
    _carToGateId.erase(carId);
    _gateController.releaseGate(gateId);
}

} // namespace Parking
