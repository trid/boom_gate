//
// Created by TriD on 15.02.2022.
//

#ifndef BOOM_GATE_APPLICATION_GATES_CONTROLLER_FACTORY_H
#define BOOM_GATE_APPLICATION_GATES_CONTROLLER_FACTORY_H

#include <memory>

namespace Gates {

class GatesController;

class GatesControllerFactory {
public:
    static std::unique_ptr<GatesController> create();
};

} // namespace Gates

#endif //BOOM_GATE_APPLICATION_GATES_CONTROLLER_FACTORY_H
