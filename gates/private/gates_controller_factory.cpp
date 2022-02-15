//
// Created by TriD on 15.02.2022.
//

#include "../public/gates_controller_factory.h"

#include "default_gate_controller.h"
#include "../public/gate.h"

namespace Gates {

// static
std::unique_ptr<GatesController> GatesControllerFactory::create() {
    return std::make_unique<DefaultGateController>();
}

} // namespace Gates