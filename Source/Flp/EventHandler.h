#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include "EventReader.h"
#include "FlpTypes.h"
#include <functional>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

template <EventSize Size>
struct HandleableEvent
{
    using ArgType = typename EventSizeDataType<Size>::DataType;
    ArgType data;

    explicit HandleableEvent(ArgType d) : data{ d } {}
};

// --------------------------------------------------------------------------------

class EventHandler
{
public:
    template<EventSize Size>
    using FnType = std::function<void(HandleableEvent<Size>)>;

    template<EventType Type, EventSize Size = EventTypeDataSize<Type>::DataType>
    void addHandler(FnType<Size> fn)
    {
        m_fn = fn;
    }

    void dispatch(EventReader &reader)
    {
        while(reader.hasEvents())
        {
            auto e = reader.getNextEvent();
            const auto type = e.getType();
            if(type == EventType::Version)
                m_fn(HandleableEvent<EventSize::Variable>{ e.getDataVariable() });
        }
    }

private:
    FnType<EventSize::Variable> m_fn;
};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------
