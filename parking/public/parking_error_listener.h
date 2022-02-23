//
// Created by TriD on 24.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PARKINGERRORLISTENER_H
#define BOOM_GATE_APPLICATION_PARKINGERRORLISTENER_H

#include <string>

namespace Parking {
class ParkingErrorListener {
public:
    virtual ~ParkingErrorListener() = default;

    virtual void onError(const std::string& description) = 0;
};
} // namespace Parking

#endif //BOOM_GATE_APPLICATION_PARKINGERRORLISTENER_H
