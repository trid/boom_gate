//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATE_CONTROLLER_BASE_H
#define BOOM_GATE_APPLICATION_GATE_CONTROLLER_BASE_H

#include <vector>

#include "../../gates/public/gates_defs.h"
#include "parking_impl.h"

namespace Parking {

class GateControllerBase {
public:
    void addGate(GateUPtr gate);
    void releaseGate(std::size_t gateId);
    void closeGate(std::size_t gateId);

private:
    void checkGateValid(size_t gateId);

    std::vector<GateUPtr> _gates;
};

}

#endif //BOOM_GATE_APPLICATION_GATE_CONTROLLER_BASE_H
