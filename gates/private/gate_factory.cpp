//
// Created by TriD on 08.02.2022.
//

#include "../public/gate_factory.h"

#include "print_gate.h"

namespace Gates {

// static
std::unique_ptr<Gate> GateFactory::create() {
    return std::make_unique<PrintGate>(std::cout);
}
} // namespace Gates