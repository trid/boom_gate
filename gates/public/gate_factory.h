//
// Created by TriD on 08.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATE_FACTORY_H
#define BOOM_GATE_APPLICATION_GATE_FACTORY_H

#include <memory>

namespace Gates {

class Gate;

class GateFactory {
public:
    static std::unique_ptr<Gate> create();
};

} // namespace Gates

#endif //BOOM_GATE_APPLICATION_GATE_FACTORY_H
