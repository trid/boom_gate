//
// Created by TriD on 15.02.2022.
//

#include "gate_controller_base.h"

#include "../../gates/public/gate.h"

namespace Parking {

void GateControllerBase::addGate(Gates::GateUPtr gate) {
    _gates.push_back(std::move(gate));
}

void GateControllerBase::releaseGate(std::size_t gateId) {
    checkGateValid(gateId);
    auto& gate = _gates[gateId];
    gate->open();
    // TODO wait for car to drive through
    gate->close();
}

void GateControllerBase::checkGateValid(size_t gateId) {
    if (gateId >= _gates.size()) {
        // TODO Log error here
    }
}

void GateControllerBase::closeGate(std::size_t gateId) {
    checkGateValid(gateId);
    auto& gate = _gates[gateId];
    gate->close();
}

} // namespace Gates