//
// Created by TriD on 07.02.2022.
//

#include "parking_impl.h"

namespace Parking {

ParkingImpl::ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                         std::unique_ptr<Billing::BillingSystem> billingSystem,
                         std::unordered_map<std::string, unsigned int>& carsRegistry) : _paymentSystem(
        std::move(paymentSystem)), _billingSystem(std::move(billingSystem)), _carsRegistry(carsRegistry) {}

void ParkingImpl::addGate(ParkingImpl::GateUPtr gate) {
    _gates.push_back(std::move(gate));
}

void ParkingImpl::tick(EventProducer& eventProducer) {
    while (eventProducer.hasEvents()) {
        auto event = eventProducer.poll();
        switch (event.type) {
            case EventType::CarEnters:
                carEnters(std::get<CarEnterData>(event.eventData));
                break;
            case EventType::CarLeaves:
                carLeaves(std::get<CarLeaveData>(event.eventData));
                break;
            case EventType::Payment:
                payed(std::get<PaymentData>(event.eventData));
                break;
        }
    }

    // TODO: Make tick counter an external dependency
    ++_tickNumber;
}

void ParkingImpl::carEnters(CarEnterData& data) {
    checkGateValid(data.gateId);

    _carsRegistry[data.carId] = _tickNumber;

    releaseGate(data.gateId);
}

void ParkingImpl::carLeaves(CarLeaveData& data) {
    checkGateValid(data.gateId);

    std::unique_ptr<Gates::Gate>& gate = _gates[data.gateId];
    // Ensure gate is closed
    gate->close();

    _carToGateId[data.carId] = data.gateId;
    auto billingAmount = _billingSystem->getBill(data.carId, _tickNumber);
    if (_billingListener) {
        _billingListener->billedFor(data.gateId, billingAmount);
    }
}

bool ParkingImpl::checkGateValid(const std::size_t gateId) const {
    if (gateId >= _gates.size()) {
        // TODO Log error here
        return false;
    }
    return true;
}

void ParkingImpl::releaseGate(const size_t gateId) {
    std::unique_ptr<Gates::Gate>& gate = _gates[gateId];
    gate->open();
    // TODO wait for car to drive through
    gate->close();
}

void ParkingImpl::payed(const PaymentData& data) {
    _paymentSystem->pay(data.paymentType, data.amount, data.cardId, [this, data](Payments::PaymentResult result) {
        onPaymentEvent(data.carId, result);
    });
}

void ParkingImpl::onPaymentEvent(const std::string& carId, const Payments::PaymentResult& result) {
    if (result != Payments::Accepted) {
        // TODO Log payment errors
        return;
    }

    auto gateId = _carToGateId[carId];
    _carsRegistry.erase(carId);
    _carToGateId.erase(carId);
    releaseGate(gateId);
}

void ParkingImpl::setBillingListener(BillingInformationListener& billingListener) {
    // TODO Is it possible to have an array of listeners here?
    _billingListener = billingListener;
}

} // namespace Parking