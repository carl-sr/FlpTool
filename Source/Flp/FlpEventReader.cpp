#include "FlpEventReader.h"
#include "FlpTypes.h"
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
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Byte) };
    assert(b);

    std::uint8_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::uint16_t flp::FlpEventReader::Event::getDataWord()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Word) };
    assert(b);

    std::uint16_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::uint32_t flp::FlpEventReader::Event::getDataDword()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Dword) };
    assert(b);

    std::uint32_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::vector<std::uint8_t> flp::FlpEventReader::Event::getDataVariable()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ FlpTypeMatchesSize(m_type, FlpEventSize::Variable) };
    assert(b);

    std::vector<std::uint8_t> r;
    auto size{ ReadVarDataLength(m_read) };

    r.reserve(size);

    for (std::size_t i = 0; i < size; ++i)
    {
        std::uint8_t u{ 0 };
        m_read.read(reinterpret_cast<char*>(&u), sizeof(u));
        r.push_back(u);
    }

    return r;
}

// --------------------------------------------------------------------------------

bool flp::FlpEventReader::Event::isExpired() const
{
    return false;
}

// --------------------------------------------------------------------------------

flp::FlpEventReader::Event::~Event()
{
    if (m_isConsumed)
        return;

    switch (GetEventSize(m_type))
    {
    case FlpEventSize::Byte:
        skipBytes(1);
        break;
    case FlpEventSize::Word:
        skipBytes(2);
        break;
    case FlpEventSize::Dword:
        skipBytes(4);
        break;
    case FlpEventSize::Variable:
        skipBytes(ReadVarDataLength(m_read));
        break;
    default:
        assert(false);
        break;
    }
}

// --------------------------------------------------------------------------------

flp::FlpEventReader::Event::Event(std::istream& read)
    : m_read(read)
    , m_type([&read]() { char u; read.get(u); return static_cast<FlpEventType>(u); }())
{
}

// --------------------------------------------------------------------------------

void flp::FlpEventReader::Event::skipBytes(std::size_t byteCount)
{
    int pos = m_read.tellg();
    m_read.seekg(pos + static_cast<int>(byteCount), std::ios::beg);
    return;
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
    return m_read.peek() != EOF;
}

// --------------------------------------------------------------------------------
