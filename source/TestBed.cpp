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

    // AI BEHAVIOURS
    liquid::parser::ParserXML behaviourParserXML;
    behaviourParserXML.parseFile("decisionTree.xml");
    liquid::ai::BehaviourTreeParser behaviourParser(behaviourParserXML);

    liquid::ai::BehaviourTree* tree = new liquid::ai::BehaviourTree();
    liquid::ai::RepeaterNode* node0 = new liquid::ai::RepeaterNode();
    liquid::ai::SequenceNode* node1 = new liquid::ai::SequenceNode();
    liquid::ai::LeafNode* node2 = new liquid::ai::LeafNode();
    liquid::ai::LeafNode* node4 = new liquid::ai::LeafNode();
    liquid::ai::InverterNode* node3 = new liquid::ai::InverterNode();

    node0->insertChild(node1);
    node0->setRepeaterLimit(0);
    node1->insertChild(node2);
    node1->insertChild(node4);
    //node3->insertChild(node4);
    tree->setNodeRoot(node0);

    node2->setFuncProcess([]()->uint32_t { return 1; });
    node4->setFuncProcess([]()->uint32_t { return 2; });

    //tree->setNodeRoot(behaviourParser.getConstructedNode());

    while (tree->getNodeState() == 0)
        tree->process();

    // ADD TEST CALLS HERE
    Tests tests;
    sf::Texture texture, texture2, texture3, uiTexture;
    texture.loadFromFile("test.png");
    texture2.loadFromFile("test2.png");
    texture3.loadFromFile("dude_animation_sheet.png");
    uiTexture.loadFromFile("interface.png");

    tests.interface(uiTexture);
    tests.particles(texture2); 
    //tests.animation(texture3);
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
