#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include "EventReader.h"
#include "FlpTypes.h"
#include <functional>
#include <map>

// --------------------------------------------------------------------------------

BEGIN_NAMESPACE_FLP

// --------------------------------------------------------------------------------

template <EventSize Size>
struct HandleableEvent
{
    const EventType type;

    using ArgType = typename EventSizeDataType<Size>::DataType;
    const ArgType data;

    explicit HandleableEvent(const EventType t, const ArgType d) : type{ t }, data{ d } {}
};

// --------------------------------------------------------------------------------

class EventHandler
{
public:
    template<EventSize Size>
    using FnType = std::function<void(HandleableEvent<Size>)>;

    template<EventType Type>
    void addHandler(FnType<EventTypeDataSize<Type>::size> fn)
    {
        internalAddHandler<Type, EventTypeDataSize<Type>::size>(fn);
    }

    void dispatch(EventReader &reader);

private:
    template<EventType Type, EventSize Size>
    requires (Size == EventSize::Byte)
    void internalAddHandler(FnType<Size> fn)
    {
        m_byteEventHandler[Type] = fn;
    }

    template<EventType Type, EventSize Size>
    requires (Size == EventSize::Word)
    void internalAddHandler(FnType<Size> fn)
    {
        m_wordEventHandler[Type] = fn;
    }

    template<EventType Type, EventSize Size>
    requires (Size == EventSize::Dword)
    void internalAddHandler(FnType<Size> fn)
    {
        m_dwordEventHandler[Type] = fn;
    }

    template<EventType Type, EventSize Size>
    requires (Size == EventSize::Variable)
    void internalAddHandler(FnType<Size> fn)
    {
        m_variableEventHandler[Type] = fn;
    }

    template<EventSize Size>
    using FnMap = std::map<EventType, FnType<Size>>;

    FnMap<EventSize::Byte> m_byteEventHandler;
    FnMap<EventSize::Word> m_wordEventHandler;
    FnMap<EventSize::Dword> m_dwordEventHandler;
    FnMap<EventSize::Variable> m_variableEventHandler;
};

// --------------------------------------------------------------------------------

END_NAMESPACE_FLP

// --------------------------------------------------------------------------------
