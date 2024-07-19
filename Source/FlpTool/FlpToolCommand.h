#pragma once

// --------------------------------------------------------------------------------

#include "Flp/Flp.h"
#include <string>
#include <span>
#include <vector>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

enum class FlpToolCommand
{

    Invalid,
    Registered,
    MainPitch,
    PluginColor,
    Version,
};

// --------------------------------------------------------------------------------

FlpToolCommand StringToFlpToolCommand(const std::string &string);

// --------------------------------------------------------------------------------

std::string FlpToolCommandToString(FlpToolCommand command);

// --------------------------------------------------------------------------------

std::vector<FlpToolCommand> StringListToFlpToolCommands(std::span<const std::string> argv);

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------