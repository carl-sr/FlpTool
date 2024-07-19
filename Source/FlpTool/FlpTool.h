#pragma once

// --------------------------------------------------------------------------------

#include "Flp/Flp.h"
#include <string>
#include <span>
#include "FlpToolCommand.h"
#include "Flp/EventHandler.h"
#include "nlohmann/json.hpp"

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

class FlpTool
{
public:
    FlpTool(const std::string &filename, const std::span<FlpToolCommand> &commands);

    nlohmann::json m_outputJson;

private:
    void handleRegistered(HandleableEvent<EventSize::Byte> e);
    void handleMainPitch(HandleableEvent<EventSize::Word> e);
    void handlePluginColor(HandleableEvent<EventSize::Dword> e);
    void handleVersion(HandleableEvent<EventSize::Variable> e);
};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------