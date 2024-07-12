#include "FlpTypes.h"

#include <algorithm>
#include <string_view>
#include <span>
#include <ranges>

// --------------------------------------------------------------------------------

bool flp::FLhd::isValid() const
{
    const auto current{ std::string_view{ magic, sizeof(magic) } };
    const bool magicValid{ current == "FLhd" };
    return magicValid;
}

// --------------------------------------------------------------------------------

bool flp::FLdt::isValid() const
{
    const bool magicValid{ std::string_view{ magic, sizeof(magic) } == "FLdt" };
    return magicValid;
}

// --------------------------------------------------------------------------------

bool flp::FlpTypeMatchesSize(FlpEventType type, FlpEventSize size)
{
    const auto u8Type{ static_cast<std::uint8_t>(type) };
    const auto u8Size{ static_cast<std::uint8_t>(size) };

    return (u8Type & u8Size) == u8Type;
}

// --------------------------------------------------------------------------------

flp::FlpEventSize flp::GetEventSize(FlpEventType type)
{
    auto u8Type{ static_cast<std::uint8_t>(type) };
    u8Type &= 0b11 << 6;

    // std::ranges::count_if({ FlpEventDataSize::Byte, FlpEventDataSize::Word, FlpEventDataSize::Dword, FlpEventDataSize::Variable }, [u8Type](const std::uint8_t t) { return t == u8Type; });

    return static_cast<FlpEventSize>(u8Type);
}

// --------------------------------------------------------------------------------
