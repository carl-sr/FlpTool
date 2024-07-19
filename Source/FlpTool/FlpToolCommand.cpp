#include "FlpToolCommand.h"
#include <ranges>

// --------------------------------------------------------------------------------

struct CommandPair
{
    flp::FlpToolCommand command;
    const char *string;
};

// --------------------------------------------------------------------------------

const static std::vector<CommandPair> Commands
{
    CommandPair{ flp::FlpToolCommand::Registered, "registered" },
    CommandPair{ flp::FlpToolCommand::MainPitch, "main_pitch" },
    CommandPair{ flp::FlpToolCommand::PluginColor, "plugin_color" },
    CommandPair{ flp::FlpToolCommand::Version, "version" },
};

// --------------------------------------------------------------------------------

flp::FlpToolCommand flp::StringToFlpToolCommand(const std::string& string)
{
    const auto it = std::ranges::find_if(Commands, [&string](auto commandPair) { return commandPair.string == string; });
    if (it != Commands.end())
        return it->command;

    return FlpToolCommand::Invalid;
}

// --------------------------------------------------------------------------------

std::string flp::FlpToolCommandToString(FlpToolCommand command)
{
    const auto it = std::ranges::find_if(Commands, [&command](auto commandPair) { return commandPair.command == command; });
    if (it != Commands.end())
        return it->string;

    return "invalid";
}

// --------------------------------------------------------------------------------

std::vector<flp::FlpToolCommand> flp::StringListToFlpToolCommands(const std::span<const std::string> argv)
{
    std::vector<FlpToolCommand> r;

    for(const auto &arg : argv)
    {
        const auto c = StringToFlpToolCommand(arg);
        if(c != FlpToolCommand::Invalid)
            r.push_back(c);
    }

    return r;
}

// --------------------------------------------------------------------------------
