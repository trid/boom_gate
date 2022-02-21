//
// Created by TriD on 15.02.2022.
//

#include "default_gate_controller.h"

#include "../public/gate.h"

void Gates::DefaultGateController::addGate(std::unique_ptr<Gate> gate) {
    _gates.push_back(std::move(gate));
}

void Gates::DefaultGateController::releaseGate(std::size_t gateId) {
    checkGateValid(gateId);
    auto& gate = _gates[gateId];
    gate->open();
    // TODO wait for car to drive through
    gate->close();
}

void Gates::DefaultGateController::checkGateValid(size_t gateId) {
    if (gateId >= _gates.size()) {
        // TODO Log error here
    }
}

void Gates::DefaultGateController::closeGate(std::size_t gateId) {
    checkGateValid(gateId);
    auto& gate = _gates[gateId];
    gate->close();
}
