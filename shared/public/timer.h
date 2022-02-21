//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_TIMER_H
#define BOOM_GATE_APPLICATION_TIMER_H

namespace Utils {
class Timer {
public:
    virtual void tick() = 0;
    [[nodiscard]] virtual unsigned int getTicks() const = 0;
};
}

#endif //BOOM_GATE_APPLICATION_TIMER_H
