//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_DEFAULT_GATE_CONTROLLER_H
#define BOOM_GATE_APPLICATION_DEFAULT_GATE_CONTROLLER_H

#include <vector>

#include "../public/gates_controller.h"

namespace Gates {

using GateUPtr = std::unique_ptr<Gates::Gate>;

class DefaultGateController: public GatesController {
public:
    void addGate(std::unique_ptr<Gate> gate) override;
    void releaseGate(std::size_t gateId) override;

    void closeGate(std::size_t gateId) override;

private:
    void checkGateValid(size_t gateId);

    std::vector<GateUPtr> _gates;
};

}

#endif //BOOM_GATE_APPLICATION_DEFAULT_GATE_CONTROLLER_H
