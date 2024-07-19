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
    printf("registered: 0x%02x\n", e.data);
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handleMainPitch(HandleableEvent<EventSize::Word> e)
{
    printf("main pitch: 0x%04x\n", e.data);
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handlePluginColor(HandleableEvent<EventSize::Dword> e)
{
    printf("plugin color: 0x%08x\n", e.data);
}

// --------------------------------------------------------------------------------

void flp::FlpTool::handleVersion(HandleableEvent<EventSize::Variable> e)
{
    std::span<const std::uint8_t> data{ e.data };
    std::string s;
    for(const auto d : data)
    {
        if (d)
            s += static_cast<char>(d);
    }
    printf("version: %s\n", s.c_str());
}

// --------------------------------------------------------------------------------
