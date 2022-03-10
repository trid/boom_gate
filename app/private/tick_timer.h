//
// Created by TriD on 21.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_TICK_TIMER_H
#define BOOM_GATE_APPLICATION_TICK_TIMER_H

#include "../../shared/public/timer.h"

class TickTimer: public Utils::Timer {
public:
    void tick() override;
    [[nodiscard]] unsigned int getTicks() const override;

private:
    unsigned int _ticksCount = 0;
};


#endif //BOOM_GATE_APPLICATION_TICK_TIMER_H
