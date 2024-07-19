#include "FlpToolCommand.h"
#include <ranges>

// --------------------------------------------------------------------------------

std::vector<flp::FlpToolCommand> flp::StringListToFlpToolCommands(const std::span<const std::string> argv)
{
    using CommandPair = std::pair<FlpToolCommand, const char *>;
    std::vector<CommandPair> commands
    {
        std::make_pair(FlpToolCommand::Registered, "registered"),
        std::make_pair(FlpToolCommand::MainPitch, "mainpitch"),
        std::make_pair(FlpToolCommand::PluginColor, "plugincolor"),
        std::make_pair(FlpToolCommand::Version, "version"),
    };

    std::vector<FlpToolCommand> r;

    for(const auto &arg : argv)
    {
        const auto it = std::ranges::find_if(commands, [&arg](auto commandPair) { return commandPair.second == arg; });
        if (it != commands.end())
            r.push_back(it->first);
    }

    return r;
}

// --------------------------------------------------------------------------------