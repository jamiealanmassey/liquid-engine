#include "LiquidEngine.h"
#include "Tests.h"

#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

int main()
{
    liquid::data::Bindings* bindings = new liquid::data::Bindings;
    bindings->parseString(bindings->mDefaultBindings);

    liquid::data::Settings* settings = new liquid::data::Settings;
    settings->parseString(settings->mDefaultSettings);

    // TODO: Make GameScene dependant on the RENDERER not the Renderer dependant on GAMESCENE
    liquid::common::GameScene* scene = new liquid::common::GameScene();
    liquid::impl::SFMLRenderer* renderer = new liquid::impl::SFMLRenderer(scene, settings);
    liquid::impl::SFMLEventManager* eventMgr = new liquid::impl::SFMLEventManager(renderer);

    liquid::common::GameManager::instance().setBindingsClass(bindings);
    liquid::common::GameManager::instance().setSettingsClass(settings);
    liquid::common::GameManager::instance().setEventManagerClass(eventMgr);
    liquid::common::GameManager::instance().setRendererClass(renderer);
    liquid::common::GameManager::instance().addGameSceneBack(scene);

    // ADD TEST CALLS HERE
    Tests tests;
    sf::Texture texture, texture2, texture3;
    texture.loadFromFile("test.png");
    texture2.loadFromFile("test2.png");
    texture3.loadFromFile("dude_animation_sheet.png");

    //tests.batchedSFMLRendering(texture);
    tests.particles(texture2);
    tests.navigation();
    //tests.animation(texture3);

    liquid::events::EventDispatcher<liquid::events::KeyboardEventData>::addListener(
        [](const liquid::events::KeyboardEventData& evnt)->bool
        {
            if (evnt.mKeyCode == sf::Keyboard::Escape)
                liquid::common::GameManager().instance().setGameRunning(false);

            return true;
        }
    );

    liquid::common::GameManager::instance().execute();
    liquid::common::GameManager::instance().simulate();
    liquid::common::GameManager::instance().terminate();
}
