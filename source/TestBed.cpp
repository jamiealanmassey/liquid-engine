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
    liquid::parser::ParserXML interfaceParser;
    interfaceParser.parseFile("interfaceAtlas.xml");

    liquid::data::TextureAtlas interfaceAtlas(interfaceParser);
    liquid::ui::WidgetManager* widgetMgr = new liquid::ui::WidgetManager(interfaceAtlas);
    liquid::common::GameScene* scene = new liquid::common::GameScene();
    scene->setWidgetManager(widgetMgr);
    
    liquid::impl::SFMLRenderer* renderer = new liquid::impl::SFMLRenderer(scene, settings);
    liquid::impl::SFMLEventManager* eventMgr = new liquid::impl::SFMLEventManager(renderer);

    liquid::common::GameManager::instance().setBindingsClass(bindings);
    liquid::common::GameManager::instance().setSettingsClass(settings);
    liquid::common::GameManager::instance().setEventManagerClass(eventMgr);
    liquid::common::GameManager::instance().setRendererClass(renderer);
    liquid::common::GameManager::instance().addGameSceneBack(scene);

    float screenWidth = settings->getScreenWidth();
    float screenHeight = settings->getScreenHeight();

    liquid::impl::SFMLCamera* camera = 
        new liquid::impl::SFMLCamera(screenWidth / 2.0f, screenHeight / 2.0f,
            screenWidth, screenHeight);

    renderer->setCamera(camera);
    camera->shake(100.0f, 30.0f, liquid::graphics::ICamera::SHAKEAXIS_XY);

    // WIDGETS
    sf::Texture uiTexture;
    uiTexture.loadFromFile("interface.png");

    liquid::impl::SFMLRenderableBatch* batch = new liquid::impl::SFMLRenderableBatch(uiTexture, 5);
    liquid::ui::Button* button = new liquid::ui::Button(20.f, 10.f, { "ButtonDefault", "ButtonPressed", "ButtonDisabled" });
    liquid::ui::Toggle* toggle = new liquid::ui::Toggle(20.f, 70.f, { "ButtonDefault", "ButtonDisabled", "" });
    
    liquid::ui::Toggle* checkbox0 = new liquid::ui::Toggle(20.0f, 135.0f, { "CheckboxDefault", "CheckboxSelected" });
    liquid::ui::Toggle* checkbox1 = new liquid::ui::Toggle(20.0f, 155.0f, { "CheckboxDefault", "CheckboxSelected" });
    liquid::ui::Toggle* checkbox2 = new liquid::ui::Toggle(20.0f, 175.0f, { "CheckboxDefault", "CheckboxSelected" });
    liquid::ui::ControlList* list = new liquid::ui::ControlList(20.0f, 135.0f, { "", "" });

    list->insertElement(checkbox0);
    list->insertElement(checkbox1);
    list->insertElement(checkbox2);
    list->setSize(20.0f, 60.0f);
    list->setControlType(liquid::ui::ControlList::CONTROLTYPE_SINGLE);

    checkbox0->setCanEnter(false);
    checkbox1->setCanEnter(false);
    checkbox2->setCanEnter(false);

    checkbox0->setVerticesPtr(batch->nextVertices());
    checkbox1->setVerticesPtr(batch->nextVertices());
    checkbox2->setVerticesPtr(batch->nextVertices());
    button->setVerticesPtr(batch->nextVertices());
    toggle->setVerticesPtr(batch->nextVertices());

    widgetMgr->insertWidget(checkbox0);
    widgetMgr->insertWidget(checkbox1);
    widgetMgr->insertWidget(checkbox2);
    widgetMgr->insertWidget(list);
    widgetMgr->insertWidget(toggle);
    widgetMgr->insertWidget(button);
    renderer->addRenderable(batch);

    // ADD TEST CALLS HERE
    Tests tests;
    sf::Texture texture, texture2, texture3;
    texture.loadFromFile("test.png");
    texture2.loadFromFile("test2.png");
    texture3.loadFromFile("dude_animation_sheet.png");

    tests.particles(texture2); 
    tests.animation(texture3);
    //tests.lighting();
    //tests.navigation();
    //tests.batchedSFMLRendering(texture);

    liquid::events::EventDispatcher<liquid::events::KeyboardEventData>::addListener(
        [&cam = camera](const liquid::events::KeyboardEventData& evnt)->bool
            {
                if (evnt.mKeyCode == sf::Keyboard::Escape)
                    liquid::common::GameManager().instance().setGameRunning(false);
                else if (evnt.mKeyCode == sf::Keyboard::A)
                    cam->setCentre({ cam->getCentre()[0] - 10.0f, cam->getCentre()[1] });
                else if (evnt.mKeyCode == sf::Keyboard::D)
                    cam->setCentre({ cam->getCentre()[0] + 10.0f, cam->getCentre()[1] });
                else if (evnt.mKeyCode == sf::Keyboard::W)
                    cam->setCentre({ cam->getCentre()[0], cam->getCentre()[1] - 10.0f });
                else if (evnt.mKeyCode == sf::Keyboard::S)
                    cam->setCentre({ cam->getCentre()[0], cam->getCentre()[1] + 10.0f });
                else if (evnt.mKeyCode == sf::Keyboard::Space)
                    cam->shake(100.0f, 25.f, liquid::graphics::ICamera::SHAKEAXIS_XY);

                return true;
            }
    );

    liquid::common::GameManager::instance().execute();
    liquid::common::GameManager::instance().simulate();
    liquid::common::GameManager::instance().terminate();
}
