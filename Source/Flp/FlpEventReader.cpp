#include "FlpEventReader.h"
#include <cassert>

// --------------------------------------------------------------------------------

flp::FlpEventReader::FlpEventReader(std::istream& read)
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

flp::FlpEventType flp::FlpEventReader::Event::getType() const
{
    return m_type;
}

// --------------------------------------------------------------------------------

std::uint8_t flp::FlpEventReader::Event::getDataByte()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Byte) };
    assert(b);
    return 0;
}

// --------------------------------------------------------------------------------

std::uint16_t flp::FlpEventReader::Event::getDataWord()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Word) };
    assert(b);
    return 0;
}

// --------------------------------------------------------------------------------

std::uint32_t flp::FlpEventReader::Event::getDataDword()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Dword) };
    assert(b);
    return 0;
}

// --------------------------------------------------------------------------------

std::vector<std::uint8_t> flp::FlpEventReader::Event::getDataVariable()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Variable) };
    assert(b);
    return {};
}

// --------------------------------------------------------------------------------

bool flp::FlpEventReader::Event::isExpired() const
{
    return false;
}

// --------------------------------------------------------------------------------

flp::FlpEventReader::Event::Event(std::istream& read)
    : m_read(read)
    , m_type([&read]() { char u; read.get(u); return static_cast<FlpEventType>(u); }())
{
}

// --------------------------------------------------------------------------------

flp::FlpEventReader::Event flp::FlpEventReader::getNextEvent()
{
    const Event e{ m_read };
    return e;
}

// --------------------------------------------------------------------------------

bool flp::FlpEventReader::hasEvents()
{
    return !m_read.eof();
}

// --------------------------------------------------------------------------------
