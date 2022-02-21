//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATES_CONTROLLER_H
#define BOOM_GATE_APPLICATION_GATES_CONTROLLER_H

#include <memory>

namespace Gates {

class Gate;

class GatesController {
public:
    virtual ~GatesController() = default;

    virtual void addGate(std::unique_ptr<Gate> gate) = 0;
    virtual void releaseGate(std::size_t gateId) = 0;
    virtual void closeGate(std::size_t gateId) = 0;
};

}

#endif //BOOM_GATE_APPLICATION_GATES_CONTROLLER_H
