#pragma once

// --------------------------------------------------------------------------------

#include "Flp/Flp.h"
#include <string>
#include <span>
#include <vector>

#include "FlpToolCommand.h"
#include "Flp/EventHandler.h"

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

class FlpTool
{
public:
    FlpTool(const std::string &filename, const std::span<FlpToolCommand> &commands);

private:

    void handleRegistered(HandleableEvent<EventSize::Byte> e);
    void handleMainPitch(HandleableEvent<EventSize::Word> e);
    void handlePluginColor(HandleableEvent<EventSize::Dword> e);
    void handleVersion(HandleableEvent<EventSize::Variable> e);
};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------