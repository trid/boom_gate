//
// Created by TriD on 21.02.2022.
//

#include "tick_timer.h"

void TickTimer::tick() {
    ++_ticksCount;
}

unsigned int TickTimer::getTicks() const {
    return _ticksCount;
}
