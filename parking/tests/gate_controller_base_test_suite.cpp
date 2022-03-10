//
// Created by TriD on 15.02.2022.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../private/gate_controller_base.h"
#include "../../gates/public/gate.h"

namespace Parking::Test {

class GateMock: public Gates::Gate {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    bool isOpen() const override { return true; }
};

TEST(DefaultGateControllerTestSuite, releaseGateOpensAndClosesTheGate) {
    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open);
    EXPECT_CALL(*gate, close);

    GateControllerBase gateController;
    gateController.addGate(std::move(gate));

    gateController.releaseGate(0);
}

TEST(DefaultGateControllerTestSuite, closeGateGateOnlyClosed) {
    auto gate = std::make_unique<GateMock>();
    EXPECT_CALL(*gate, open).Times(0);
    EXPECT_CALL(*gate, close);

    GateControllerBase gateController;
    gateController.addGate(std::move(gate));

    gateController.closeGate(0);
}

} // namespace Gates::Test