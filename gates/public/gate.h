//
// Created by TriD on 04.02.2022.
//

#ifndef BOOM_GATE_GATE_H
#define BOOM_GATE_GATE_H

namespace Gates {

class Gate {
public:
    virtual ~Gate() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    [[nodiscard]] virtual bool isOpen() const = 0;
};

}

#endif //BOOM_GATE_GATE_H
