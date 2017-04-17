#include <functional>
#include <map>
#include "EventDispatcher.h"

namespace liquid { namespace events {
#ifndef _EVENTMANAGER_H
#define _EVENTMANAGER_H

/**
 * \class EventManager
 *
 * \ingroup Events
 * \brief Interface class to handle incoming Events
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 09/04/2017
 *
 */

class EventManager
{
public:
    /// EventManager Constructor
    EventManager();

    /// EventManager Destructor
    ~EventManager();

    /** \brief Updates any incoming events
      *
      * Extendable class to handle updating of Events, use the EventDispatch class
      * in conjunction with the EventData class to dispatch events accordingly when
      * desired input event have come in.
      */
    virtual void updateEvents() = 0;
};

#endif // _EVENTMANAGER_H
}}
