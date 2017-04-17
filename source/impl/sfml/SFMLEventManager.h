//#ifdef SFML
#include "../../events/EventManager.h"

namespace liquid { namespace impl {
#ifndef _SFMLEVENTMANAGER_H
#define _SFMLEVENTMANAGER_H

/**
 * \class SFMLEventManager
 *
 * \ingroup Impl
 * \brief Defines how the events::EventManager should function when using SFML
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 17/04/2017
 *
 */

class SFMLRenderer;
class SFMLEventManager : public events::EventManager
{
public:
    /** \brief SFMLEventManager Constructor
      * \param parentRenderer Pointer to the Parent Renderer of this EventManager
      */
    SFMLEventManager(SFMLRenderer* parentRenderer);

    /// SFMLEventManager Destructor
    ~SFMLEventManager();

    /// Override for processing events
    void updateEvents() override;

protected:
    SFMLRenderer* mParentRenderer; ///< Pointer to te Parent Renderer of the EventManager
};

#endif // _SFMLEVENTMANAGER_H
}}

//#endif // SFML
