//
// Created by TriD on 04.02.2022.
//

#include "gtest/gtest.h"

#include <sstream>

#include "../private/print_gate.h"

namespace Gates::Tests {

TEST(BoomGateTestSuite, testNotOperated) {
    std::stringstream out;
    PrintGate boomGate{out};

    ASSERT_EQ("", out.str());
    ASSERT_FALSE(boomGate.isOpen());
}

TEST(BoomGateTestSuite, testOpen) {
    std::stringstream out;
    PrintGate boomGate{out};

    boomGate.open();

    ASSERT_EQ("Open!\n", out.str());
    ASSERT_TRUE(boomGate.isOpen());
}

TEST(BoomGateTestSuite, testClose) {
    std::stringstream out;
    PrintGate boomGate{out};

    boomGate.close();

    ASSERT_EQ("Close!\n", out.str());
    ASSERT_FALSE(boomGate.isOpen());
}

TEST(BoomGateTestSuite, testOpenClose) {
    std::stringstream out;
    PrintGate boomGate{out};

    boomGate.open();
    boomGate.close();

    ASSERT_EQ("Open!\nClose!", out.str());
    ASSERT_FALSE(boomGate.isOpen());
}

} // namespace Gates::Tests