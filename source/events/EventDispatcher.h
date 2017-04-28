#include <map>

namespace liquid { namespace events {
#ifndef _EVENTDISPATCHER_H
#define _EVENTDISPATCHER_H

/** 
 * \class EventDispatcher
 * 
 * \ingroup Events
 * \brief Defines a way to dispatch Events of a specific type by type-passing a class
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 09/04/2017
 *
 */

template<class T>
class EventDispatcher
{
public:
    typedef std::function<bool(const T&)> EventListener; ///< Defines the EventListener, simple function callback
    typedef int32_t EventHandle;                         ///< Defines the Handle for an Event Listener

public:
    /** \brief Add a listener to this dispatch event
      * \param listener std::function representation of the event listener
      * \return Returns the handle ID of the listener
      *
      * Adds a new listener to the specified dispatcher and assigning it a given
      * ID to the new listener, when this dispatcher is triggered all added listeners
      * will be called.
      */
    static EventHandle addListener(std::function<bool(const T&)> listener)
    {
        EventHandle handle = getNextHandle();
        getListenerHandlers()[handle] = listener;
        return handle;
    }

    /** \brief Removes the listener with the given Handle ID
      * \param handle The Handler ID of the listener to remove
      */
    static void removeListener(EventHandle handle)
    {
        getListenerHandlers().erase(handle);
    }

    /** \brief Triggers all the listeners of the type-casted type
      * \param evnt The given event but with specified data
      */
    static void triggerListeners(T& evnt)
    {
        for (const auto& handle : getListenerHandlers())
            handle.second(evnt);
    }

protected:
    /** \brief Returns the listener handlers for this class-type
      * \return Map with value pairs <EventDispatchHandle, EventListener>
      */
    static std::map<EventHandle, EventListener>& getListenerHandlers()
    {
        static std::map<EventHandle, EventListener> listenerHandlers;
        return listenerHandlers;
    }

    /// \return The next Event Handle for this class-type
    static EventHandle getNextHandle()
    {
        static EventHandle handleID = 0;
        return ++handleID;
    }
};

#endif // _EVENTDISPATCHER_H
}}
