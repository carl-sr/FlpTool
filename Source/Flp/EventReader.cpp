#include "EventReader.h"
#include "FlpTypes.h"
#include <cassert>

// --------------------------------------------------------------------------------

flp::EventReader::EventReader(std::istream& read)
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

flp::EventType flp::EventReader::Event::getType() const
{
    return m_type;
}

// --------------------------------------------------------------------------------

std::uint8_t flp::EventReader::Event::getDataByte()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ TypeMatchesSize(m_type, EventSize::Byte) };
    assert(b);

    std::uint8_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::uint16_t flp::EventReader::Event::getDataWord()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ TypeMatchesSize(m_type, EventSize::Word) };
    assert(b);

    std::uint16_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::uint32_t flp::EventReader::Event::getDataDword()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ TypeMatchesSize(m_type, EventSize::Dword) };
    assert(b);

    std::uint32_t r{ 0 };
    m_read.read(reinterpret_cast<char*>(&r), sizeof(r));

    return r;
}

// --------------------------------------------------------------------------------

std::vector<std::uint8_t> flp::EventReader::Event::getDataVariable()
{
    assert(!m_isConsumed);
    m_isConsumed = true;

    const auto b{ TypeMatchesSize(m_type, EventSize::Variable) };
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

bool flp::EventReader::Event::isExpired() const
{
    return false;
}

// --------------------------------------------------------------------------------

flp::EventReader::Event::~Event()
{
    if (m_isConsumed)
        return;

    switch (GetEventSize(m_type))
    {
    case EventSize::Byte:
        skipBytes(1);
        break;
    case EventSize::Word:
        skipBytes(2);
        break;
    case EventSize::Dword:
        skipBytes(4);
        break;
    case EventSize::Variable:
        skipBytes(ReadVarDataLength(m_read));
        break;
    default:
        assert(false);
        break;
    }
}

// --------------------------------------------------------------------------------

flp::EventReader::Event::Event(std::istream& read)
    : m_read(read)
    , m_type([&read]() { char u; read.get(u); return static_cast<EventType>(u); }())
{
}

// --------------------------------------------------------------------------------

void flp::EventReader::Event::skipBytes(std::size_t byteCount)
{
    int pos = m_read.tellg();
    m_read.seekg(pos + static_cast<int>(byteCount), std::ios::beg);
    return;
}

// --------------------------------------------------------------------------------

flp::EventReader::Event flp::EventReader::getNextEvent()
{
    const Event e{ m_read };
    return e;
}

// --------------------------------------------------------------------------------

bool flp::EventReader::hasEvents()
{
    return m_read.peek() != EOF;
}

// --------------------------------------------------------------------------------

void flp::EventReader::PrintAllEvents(EventReader& reader)
{
    while (reader.hasEvents())
    {
        auto e = reader.getNextEvent();

        const auto type{ static_cast<std::uint8_t>(e.getType()) };

        switch (flp::GetEventSize(e.getType()))
        {
        case flp::EventSize::Byte:
            printf("0x%02x (BYTE): 0x%02x\n", type, e.getDataByte());
            break;
        case flp::EventSize::Word:
            printf("0x%02x (WORD): 0x%04x\n", type, e.getDataWord());
            break;
        case flp::EventSize::Dword:
            printf("0x%02x (DWORD): 0x%08x\n", type, e.getDataDword());
            break;
        case flp::EventSize::Variable:
        {
            printf("0x%02x (VAR): ", type);
            for (const auto u : e.getDataVariable())
                printf("0x%02x ", u);
            printf("\n");
            break;
        }

        default:
            assert(false);
            break;
        }
    }
}

// --------------------------------------------------------------------------------

flp::EventReader::EventVariantList flp::EventReader::GetEventVariantList(EventReader& reader)
{
    EventVariantList events;

    while (reader.hasEvents())
    {
        auto e = reader.getNextEvent();

        switch (flp::GetEventSize(e.getType()))
        {
        case flp::EventSize::Byte:
            events.push_back(std::make_pair(e.getType(), e.getDataByte()));
            break;
        case flp::EventSize::Word:
            events.push_back(std::make_pair(e.getType(), e.getDataWord()));
            break;
        case flp::EventSize::Dword:
            events.push_back(std::make_pair(e.getType(), e.getDataDword()));
            break;
        case flp::EventSize::Variable:
            events.push_back(std::make_pair(e.getType(), e.getDataVariable()));
            break;

        default:
            assert(false);
            break;
        }
    }

    return events;
}

// --------------------------------------------------------------------------------
