#include "Flp.h"
#include <cassert>

// --------------------------------------------------------------------------------

Flp::Flp(std::istream& read)
    : m_read(read)
{
    read.read(reinterpret_cast<char *>(&header), sizeof(header));
    read.read(reinterpret_cast<char *>(&data), sizeof(data));

    const auto a = header.isValid();
    const auto b = data.isValid();

    assert(a);
    assert(b);

}

// --------------------------------------------------------------------------------

FlpEventType Flp::Event::getType() const
{
    return m_type;
}

// --------------------------------------------------------------------------------

std::uint8_t Flp::Event::getDataByte()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Byte) };
    assert(b);
    return 0;
}

// --------------------------------------------------------------------------------

std::uint16_t Flp::Event::getDataWord()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Word) };
    assert(b);
    return 0;
}

// --------------------------------------------------------------------------------

std::uint32_t Flp::Event::getDataDword()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Dword) };
    assert(b);
    return 0;
}

// --------------------------------------------------------------------------------

std::vector<std::uint8_t> Flp::Event::getDataVariable()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Variable) };
    assert(b);
    return {};
}

// --------------------------------------------------------------------------------

bool Flp::Event::isExpired() const
{
    return false;
}

// --------------------------------------------------------------------------------

Flp::Event::Event(std::istream& read)
    : m_read(read)
    , m_type([&read]() { char u; read.get(u); return static_cast<FlpEventType>(u); }())
{
}

// --------------------------------------------------------------------------------

Flp::Event Flp::getNextEvent()
{
    const Event e{ m_read };
    return e;
}

// --------------------------------------------------------------------------------

bool Flp::hasEvents()
{
    return !m_read.eof();
}

// --------------------------------------------------------------------------------
