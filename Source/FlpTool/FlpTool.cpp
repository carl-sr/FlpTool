#include "FlpTool.h"
#include <fstream>
#include <ranges>

#include "Flp/EventDispatcher.h"

// --------------------------------------------------------------------------------

flp::FlpTool::FlpTool(const std::string& filename, const std::span<FlpToolCommand>& commands)
{
    EventHandler handler;

    for(const auto &c : commands)
    {
#define EVENT_CASE(type, fn) case FlpToolCommand::type: handler.addHandler<EventType::type>([this](auto e) { fn(e); }); break;
        switch(c)
        {
            // BYTE
        EVENT_CASE(Registered, handleRegistered)

            // WORD
        EVENT_CASE(MainPitch, handleMainPitch)

            // DWORD
        EVENT_CASE(PluginColor, handlePluginColor)

            // VARIABLE
        EVENT_CASE(Version, handleVersion)

        default: break;
        }
    }

    std::ifstream stream{ filename, std::ios::binary };
    EventReader reader{ stream };

    handler.dispatch(reader);
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handleRegistered(HandleableEvent<EventSize::Byte> e)
{
    m_outputJson[FlpToolCommandToString(FlpToolCommand::Registered)] = e.data;
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handleMainPitch(HandleableEvent<EventSize::Word> e)
{
    m_outputJson[FlpToolCommandToString(FlpToolCommand::MainPitch)]= e.data;
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handlePluginColor(HandleableEvent<EventSize::Dword> e)
{
    std::stringstream s;
    s << "#" << std::hex << e.data;

    const auto hexString = s.str();
    m_outputJson[FlpToolCommandToString(FlpToolCommand::PluginColor)] = hexString;
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handleVersion(HandleableEvent<EventSize::Variable> e)
{
    const std::span<const std::uint8_t> data{ e.data };
    std::string s;
    for(const auto d : data)
    {
        if (d)
            s += static_cast<char>(d);
    }
    m_outputJson[FlpToolCommandToString(FlpToolCommand::Version)] = s;
}

// --------------------------------------------------------------------------------
