#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include "EventReader.h"
#include <istream>
#include <functional>
#include <span>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

class EventDispatcher
{
public:
    EventDispatcher(std::istream &read);

    void addHandler(EventType eventType, std::function<void(const std::uint8_t)> handler) {}
    // void addHandler(FlpEventType eventType, std::function<void(const std::uint16_t)> handler) {}
    // void addHandler(FlpEventType eventType, std::function<void(const std::uint32_t)> handler) {}
    // void addHandler(FlpEventType eventType, std::function<void(const std::span<const std::uint8_t>)> handler) {}

    void dispatch() {}

private:
    EventReader m_reader;

};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------
