//
// Created by TriD on 04.02.2022.
//

#include "print_gate.h"

namespace Gates {

PrintGate::PrintGate(std::ostream& output) : _output(output) {}

void Gates::PrintGate::open() {
    _output << "Open!" << std::endl;
    _isOpen = true;
}

void Gates::PrintGate::close() {
    _output << "Close!" << std::endl;
    _isOpen = false;
}

bool Gates::PrintGate::isOpen() const {
    _isOpen;
}

} // namespace Gates