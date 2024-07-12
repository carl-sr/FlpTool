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
    return GetEventSize(type) == size;
}

// --------------------------------------------------------------------------------

flp::FlpEventSize flp::GetEventSize(FlpEventType type)
{
    auto u8Type{ static_cast<std::uint8_t>(type) };
    u8Type &= 0b11 << 6;

    return static_cast<FlpEventSize>(u8Type);
}

// --------------------------------------------------------------------------------

std::size_t flp::ReadVarDataLength(std::istream& read)
{
    constexpr std::uint8_t Mask{ 0b1 << 7 }; // highest beat means the number continues

    std::size_t r{ 0 };
    std::uint8_t u{ 0 };
    do
    {
        read.read(reinterpret_cast<char*>(&u), sizeof(u));
        r += u & ~Mask;
    } while ((u & Mask) && !read.eof());

    return r;
}

// --------------------------------------------------------------------------------
