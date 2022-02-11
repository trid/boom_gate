//
// Created by TriD on 07.02.2022.
//

#include "parking_impl.h"

namespace Parking {

ParkingImpl::ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem) : _paymentSystem(
        std::move(paymentSystem)) {}

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
}

void ParkingImpl::carEnters(CarEnterData& data) {
    checkGateValid(data.gateId);

    releaseGate(data.gateId);
}

void ParkingImpl::carLeaves(CarLeaveData& data) {
    checkGateValid(data.gateId);

    std::unique_ptr<Gates::Gate>& gate = _gates[data.gateId];
    // Ensure gate is closed
    gate->close();
    // TODO Print billing information somehow
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
        onPaymentEvent(data.gateId, result);
    });
}

void ParkingImpl::onPaymentEvent(const size_t gateId, const Payments::PaymentResult& result) {
    if (result == Payments::Accepted) {
        releaseGate(gateId);
        return;
    }
    // TODO Log payment errors
}

} // namespace Parking