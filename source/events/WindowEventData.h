#include <stdint.h>

namespace liquid { namespace events {
#ifndef _WINDOWEVENTDATA_H
#define _WINDOWEVENTDATA_H

/**
 * \class WindowEventData
 *
 * \ingroup Events
 * \brief Structure of a window event, use for EventDispatcher
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 09/04/2017
 *
 */

class WindowEventData
{
public:
    /// Event Type
    enum eWindowEventType
    {
        WINDOWEVENT_LOSTFOCUS = 0,
        WINDOWEVENT_GAINFOCUS = 1,
        WINDOWEVENT_CLOSED = 2,
    };

public:
    /** \brief WindowEventData constructor
      * \param eventType Type of the window event as an enumerator
      */
    WindowEventData(eWindowEventType eventType)
    {
        mEventType = eventType;
    }

public:
    eWindowEventType mEventType; ///< Type of event that occured with window
};

#endif // _WINDOWEVENTDATA_H
}}
