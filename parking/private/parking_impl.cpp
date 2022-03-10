//
// Created by TriD on 07.02.2022.
//

#include "parking_impl.h"

#include "../../gates/public/gate.h"

namespace Parking {

ParkingImpl::ParkingImpl(std::unique_ptr<Payments::PaymentSystem> paymentSystem,
                         std::unique_ptr<GateControlStrategy> gateControlStrategy,
                         Billing::BillingSystem& billingSystem,
                         Billing::BillingInformationListener& billingInformationListener) : _paymentSystem(
        std::move(paymentSystem)),
        _gateControlStrategy(std::move(gateControlStrategy)),
        _billingSystem(billingSystem),
        _billingListener(billingInformationListener) {}

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
            case EventType::RequestBilling:
                requestBilling(std::get<RequestBillingData>(event.eventData));
                break;
        }
    }
}

void ParkingImpl::carEnters(const CarEnterData& data) {
    _gateControlStrategy->onCarEntering(data.gateId, data.accountId);
}

void ParkingImpl::carLeaves(const CarLeaveData& data) {
    _gateControlStrategy->onCarLeaving(data.gateId, data.accountId);
}

void ParkingImpl::payed(const PaymentData& data) {
    _paymentSystem->pay(data.paymentType, data.amount, data.cardId, [this, data](Payments::PaymentResult result) {
        onPaymentEvent(data.accountId, result);
    });
}

void ParkingImpl::onPaymentEvent(const boost::uuids::uuid& accountId, const Payments::PaymentResult& result) {
    _gateControlStrategy->onPayment(accountId, result);
}

void ParkingImpl::requestBilling(const RequestBillingData& data) {
    _billingListener.onBillingInformationProduced(data.accountId, _billingSystem.getBill(data.accountId));
}

} // namespace Parking