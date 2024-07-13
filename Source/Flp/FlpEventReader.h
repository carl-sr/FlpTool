#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include "FlpTypes.h"
#include <istream>
#include <vector>
#include <variant>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

class FlpEventReader
{
public:
    explicit FlpEventReader(std::istream &read);

    FLhd header;
    FLdt data;

    class Event
    {
    public:

        FlpEventType getType() const;

        std::uint8_t getDataByte();
        std::uint16_t getDataWord();
        std::uint32_t getDataDword();
        std::vector<std::uint8_t> getDataVariable();

        bool isExpired() const;

        ~Event();

    private:
        friend class FlpEventReader;

        Event(std::istream &read);

        void skipBytes(std::size_t byteCount);

        bool m_isConsumed{ false };
        std::istream &m_read;
        const FlpEventType m_type;
    };

    Event getNextEvent();
    bool hasEvents();

    static void PrintAllEvents(FlpEventReader& reader);

    using EventVariantType = std::variant<std::uint8_t, std::uint16_t, std::uint32_t, std::vector<std::uint8_t>>;
    using EventVariantList = std::vector<std::pair<flp::FlpEventType, EventVariantType>>;
    EventVariantList GetEventVariantList(FlpEventReader& reader);

private:
    std::istream &m_read;
};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------
