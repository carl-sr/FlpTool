#include "EventHandler.h"
#include <cassert>

// --------------------------------------------------------------------------------

void flp::EventHandler::dispatch(EventReader& reader)

{
    while(reader.hasEvents())
    {
        auto e = reader.getNextEvent();
        switch(const auto type = e.getType(); GetEventSize(type))
        {
        case EventSize::Byte:
            if (m_byteEventHandler.contains(type))
                m_byteEventHandler[type](HandleableEvent<EventSize::Byte>{ type, e.getDataByte() });
            break;
        case EventSize::Word:
            if (m_wordEventHandler.contains(type))
                m_wordEventHandler[type](HandleableEvent<EventSize::Word>{ type, e.getDataWord() });
            break;
        case EventSize::Dword:
            if (m_dwordEventHandler.contains(type))
                m_dwordEventHandler[type](HandleableEvent<EventSize::Dword>{ type, e.getDataDword() });
            break;
        case EventSize::Variable:
            if (m_variableEventHandler.contains(type))
                m_variableEventHandler[type](HandleableEvent<EventSize::Variable>{ type, e.getDataVariable() });
            break;
        default:
            assert(false);
        }
    }
}

// --------------------------------------------------------------------------------
