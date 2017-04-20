#ifdef SFML
#include "SFMLEventManager.h"
#include "SFMLRenderer.h"
#include "../../common/GameManager.h"
#include "../../events/KeyboardEventData.h"
#include "../../events/MouseEventData.h"
#include "../../events/WindowEventData.h"

namespace liquid {
namespace impl {

    SFMLEventManager::SFMLEventManager(SFMLRenderer* parentRenderer)
    {
        mParentRenderer = parentRenderer;
    }

    SFMLEventManager::~SFMLEventManager()
    {}

    void SFMLEventManager::updateEvents()
    {
        sf::Event nextEvent;
        while (mParentRenderer->getRenderWindow()->pollEvent(nextEvent))
        {
            if (nextEvent.type == sf::Event::KeyPressed)
            {
                events::KeyboardEventData data(nextEvent.key.code, true);
                events::EventDispatcher<events::KeyboardEventData>::triggerListeners(data);
            }
            else if (nextEvent.type == sf::Event::KeyReleased)
            {
                events::KeyboardEventData data(nextEvent.key.code, false);
                events::EventDispatcher<events::KeyboardEventData>::triggerListeners(data);
            }
            else if (nextEvent.type == sf::Event::MouseButtonPressed)
            {
                events::MouseEventData data((int32_t)nextEvent.mouseButton.button,
                                                     nextEvent.mouseButton.x, 
                                                     nextEvent.mouseButton.y, true);

                events::EventDispatcher<events::MouseEventData>::triggerListeners(data);
            }
            else if (nextEvent.type == sf::Event::MouseButtonReleased)
            {
                events::MouseEventData data((int32_t)nextEvent.mouseButton.button,
                                                     nextEvent.mouseButton.x,
                                                     nextEvent.mouseButton.y, false);

                events::EventDispatcher<events::MouseEventData>::triggerListeners(data);
            }
            else if (nextEvent.type == sf::Event::LostFocus)
            {
                events::WindowEventData data(events::WindowEventData::WINDOWEVENT_LOSTFOCUS);
                events::EventDispatcher<events::WindowEventData>::triggerListeners(data);
            }
            else if (nextEvent.type == sf::Event::GainedFocus)
            {
                events::WindowEventData data(events::WindowEventData::WINDOWEVENT_GAINFOCUS);
                events::EventDispatcher<events::WindowEventData>::triggerListeners(data);
            }
            else if (nextEvent.type == sf::Event::Closed)
                liquid::common::GameManager::instance().setGameRunning(false);
        }
    }



}}

#endif // SFML
