//
// Created by TriD on 07.02.2022.
//

#include "parking_impl.h"

#include "../../gates/public/gate.h"

namespace Parking {

ParkingImpl::ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                         std::unique_ptr<GateControlStrategy> gateControlStrategy) : _paymentSystem(
        std::move(paymentSystem)), _gateControlStrategy(std::move(gateControlStrategy)) {}

void ParkingImpl::addGate(GateUPtr gate) {
    _gateControlStrategy->addGate(std::move(gate));
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
    _gateControlStrategy->onCarEntering(data.gateId, data.carId, _tickNumber);
}

void ParkingImpl::carLeaves(CarLeaveData& data) {
    _gateControlStrategy->onCarLeaving(data.gateId, data.carId, _tickNumber);
}

void ParkingImpl::payed(const PaymentData& data) {
    _paymentSystem->pay(data.paymentType, data.amount, data.cardId, [this, data](Payments::PaymentResult result) {
        onPaymentEvent(data.carId, result);
    });
}

void ParkingImpl::onPaymentEvent(const std::string& carId, const Payments::PaymentResult& result) {
    _gateControlStrategy->onPayment(carId, result);
}

} // namespace Parking