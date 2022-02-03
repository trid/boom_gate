//
// Created by TriD on 04.02.2022.
//

#include "print_gate.h"

namespace Gates {

PrintGate::PrintGate(std::ostream& output) : _output(output) {}

void Gates::PrintGate::open() {
    _output << "Open!";
    _isOpen = true;
}

void Gates::PrintGate::close() {
    _output << "Close!";
    _isOpen = false;
}

bool Gates::PrintGate::isOpen() {
    _isOpen;
}

} // namespace Gates