#include <gtest/gtest.h>

//--------------------------------------------------------------------------------

#include "FlpTests.h"
#include "FlpToolTests.h"

//--------------------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//--------------------------------------------------------------------------------
