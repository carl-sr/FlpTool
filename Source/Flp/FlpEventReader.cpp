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

    std::uint8_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::uint16_t flp::FlpEventReader::Event::getDataWord()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Word) };
    assert(b);

    std::uint16_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::uint32_t flp::FlpEventReader::Event::getDataDword()
{
    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Dword) };
    assert(b);

    std::uint32_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
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
