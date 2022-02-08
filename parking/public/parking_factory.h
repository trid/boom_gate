//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKING_FACTORY_H
#define BOOM_GATE_APPLICATION_PARKING_FACTORY_H

#include <memory>

namespace Payments {
class PaymentSystem;
} // namespace Payments

namespace Parking {

class Parking;

class ParkingFactory {
public:
    static std::unique_ptr<Parking> create(std::unique_ptr<Payments::PaymentSystem> paymentSystem);
};

} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKING_FACTORY_H
