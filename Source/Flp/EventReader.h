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

class EventReader
{
public:
    explicit EventReader(std::istream &read);

    FLhd header;
    FLdt data;

    class Event
    {
    public:

        EventType getType() const;

        std::uint8_t getDataByte();
        std::uint16_t getDataWord();
        std::uint32_t getDataDword();
        std::vector<std::uint8_t> getDataVariable();

        bool isExpired() const;

        ~Event();

    private:
        friend class EventReader;

        Event(std::istream &read);

        void skipBytes(std::size_t byteCount);

        bool m_isConsumed{ false };
        std::istream &m_read;
        const EventType m_type;
    };

    Event getNextEvent();
    bool hasEvents();

    static void PrintAllEvents(EventReader& reader);

    using EventVariantType = std::variant<std::uint8_t, std::uint16_t, std::uint32_t, std::vector<std::uint8_t>>;
    using EventVariantList = std::vector<std::pair<flp::EventType, EventVariantType>>;
    EventVariantList GetEventVariantList(EventReader& reader);

private:
    std::istream &m_read;
};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------
