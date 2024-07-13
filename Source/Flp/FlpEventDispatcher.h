#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include "FlpEventReader.h"
#include <istream>
#include <functional>
#include <span>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

class FlpEventDispatcher
{
public:
    FlpEventDispatcher(std::istream &read);

    void addHandler(FlpEventType eventType, std::function<void(const std::uint8_t)> handler) {}
    // void addHandler(FlpEventType eventType, std::function<void(const std::uint16_t)> handler) {}
    // void addHandler(FlpEventType eventType, std::function<void(const std::uint32_t)> handler) {}
    // void addHandler(FlpEventType eventType, std::function<void(const std::span<const std::uint8_t>)> handler) {}

    void dispatch() {}

private:
    FlpEventReader m_reader;

};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------
