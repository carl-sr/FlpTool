#pragma once

// --------------------------------------------------------------------------------

#include "Flp.h"
#include "EventReader.h"
#include "FlpTypes.h"
#include <functional>
#include <cassert>
#include <map>

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

    template<EventType Type>
    void addHandler(FnType<EventTypeDataSize<Type>::size> fn)
    {
        internalAddHandler<Type, EventTypeDataSize<Type>::size>(fn);
    }

    void dispatch(EventReader &reader)
    {
        while(reader.hasEvents())
        {
            auto e = reader.getNextEvent();
            switch(const auto type = e.getType(); GetEventSize(type))
            {
            case EventSize::Byte:
                if (m_byteEventHandler.contains(type))
                    m_byteEventHandler[type](HandleableEvent<EventSize::Byte>{ e.getDataByte() });
                break;
            case EventSize::Word:
                if (m_wordEventHandler.contains(type))
                    m_wordEventHandler[type](HandleableEvent<EventSize::Word>{ e.getDataWord() });
                break;
            case EventSize::Dword:
                if (m_dwordEventHandler.contains(type))
                    m_dwordEventHandler[type](HandleableEvent<EventSize::Dword>{ e.getDataDword() });
                break;
            case EventSize::Variable:
                if (m_variableEventHandler.contains(type))
                    m_variableEventHandler[type](HandleableEvent<EventSize::Variable>{ e.getDataVariable() });
                break;
            default:
                assert(false);
            }
        }
    }

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
