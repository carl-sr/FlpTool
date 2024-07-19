#pragma once

//--------------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "FlpTool/FlpToolCommand.h"
#include <vector>

//--------------------------------------------------------------------------------

TEST(FlpToolCommand, FromString)
{
    std::vector<std::string> commandStrings{ "version" };
    auto commandList = flp::StringListToFlpToolCommands(commandStrings);

    auto contains = [&commandList](const flp::FlpToolCommand c) { return std::ranges::find(commandList, c) != commandList.end(); };

    EXPECT_TRUE(contains(flp::FlpToolCommand::Version));
}

//--------------------------------------------------------------------------------
