#include "FlpTypes.h"
#include <string_view>
#include <span>

// --------------------------------------------------------------------------------

bool FLhd::isValid() const
{
    const auto current{ std::string_view{ magic, sizeof(magic) } };
    const bool magicValid{ current == "FLhd" };
    return magicValid;
}

// --------------------------------------------------------------------------------

bool FLdt::isValid() const
{
    const bool magicValid{ std::string_view{ magic, sizeof(magic) } == "FLdt" };
    return magicValid;
}

// --------------------------------------------------------------------------------

bool FlpTypeMatchesSize(FlpEventType type, FlpEventSize size)
{
    const auto u8Type{ static_cast<std::uint8_t>(type) };
    const auto u8Size{ static_cast<std::uint8_t>(size) };

    return u8Type & u8Size == u8Type;
}

// --------------------------------------------------------------------------------
