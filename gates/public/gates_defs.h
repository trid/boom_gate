//
// Created by TriD on 22.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATES_DEFS_H
#define BOOM_GATE_APPLICATION_GATES_DEFS_H

#include <memory>

namespace Gates {
class Gate;

using GateUPtr = std::unique_ptr<Gate>;
}

#endif //BOOM_GATE_APPLICATION_GATES_DEFS_H
