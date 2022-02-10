//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_PRINT_GATE_H
#define BOOM_GATE_APPLICATION_PRINT_GATE_H

#include <iostream>

#include "../public/gate.h"

namespace Gates {

class PrintGate : public Gate {
public:
    explicit PrintGate(std::ostream& output);

    void open() override;
    void close() override;
    bool isOpen() const override;

private:
    std::ostream& _output;

    bool _isOpen = false;
};

} // namespace Gates

#endif //BOOM_GATE_APPLICATION_PRINT_GATE_H
