#include <map>
#include <algorithm>

namespace liquid { namespace common {
#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

/**
 * \class ResourceManager
 *
 * \ingroup Common
 * \brief Singleton class that allows storing of any generic data collection
 *
 * \author Jamie Massey
 * \version 2.0
 * \date 09/04/2017
 *
 */

// TODO: Implement a class that handles ID pools, use it here and in EventDispatcher

template <class T>
class ResourceManager
{
public:
    typedef int32_t ResourceID;

public:
    /** \brief Adds a new Resource to the collection defined by template class
      * \param resource Resource to be added to the collection
      * \return Next ResourceID that represents this resource
      */
    static ResourceID addResource(T* resource)
    {
        ResourceID id = getNextResourceID();
        getResources()[id] = resource;
        return id;
    }

    /** \brief Remove an existing resource from the collection
      * \param id ResourceID representing the resource you wish to remove
      */
    static void removeResource(ResourceID id)
    {
        getResources().erase(id);
    }

    /** \brief Retrieve the Resource related to the given ID
      * \param id ResourceID of the resource you wish to retrieve
      * \return The resource specified, nullptr if it doesn't exist
      */
    static T* getResource(ResourceID id)
    {
        return getResources()[id];
    }

    /// \brief Removes all Resources from this class specific store
    static void flushResources()
    {
        getResources().erase(getResources().begin(), getResources().end());
        getResources().clear();
    }

protected:
    /** \brief Returns the resources for this class-type
      * \return Map with value pairs <ResourceID, T*>
      */
    static std::map<ResourceID, T*>& getResources()
    {
        static std::map<ResourceID, T*> resources;
        return resources;
    }

    /// \return The next Event Handle for this class-type
    static ResourceID getNextResourceID()
    {
        static ResourceID resourceID = 0;
        return ++resourceID;
    }
};

#endif // _RESOURCEMANAGER_H
}}
