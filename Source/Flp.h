#pragma once

// --------------------------------------------------------------------------------

#include "FlpTypes.h"
#include <istream>
#include <vector>

// --------------------------------------------------------------------------------

class Flp
{
public:
    explicit Flp(std::istream &read);

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

    private:
        friend class Flp;

        Event(std::istream &read);


        std::istream &m_read;
        const FlpEventType m_type;
    };

    Event getNextEvent();
    bool hasEvents();

private:
    std::istream &m_read;
};

// --------------------------------------------------------------------------------
