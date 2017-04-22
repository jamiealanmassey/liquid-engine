#include "LiquidEngine.h"
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

int main()
{
    std::string configTest = "";
    configTest += "fullscreen true\n";
    configTest += "fullscreen2 False\n";
    configTest += "fullscreen3 FalSe\n";
    configTest += "fullscreen4 TRUE\n";
    configTest += "volume 100\n";
    configTest += "name configTest";

    liquid::data::ConfigurationParser* parser = new liquid::data::ConfigurationParser;
    parser->parseString(configTest);

    std::cout << "fullscreen: " << parser->getValueAsBoolean("fullscreen") << "\n";
    std::cout << "fullscreen2: " << parser->getValueAsBoolean("fullscreen2") << "\n";
    std::cout << "fullscreen3: " << parser->getValueAsBoolean("fullscreen3") << "\n";
    std::cout << "fullscreen4: " << parser->getValueAsBoolean("fullscreen4") << "\n";
    std::cout << "volume: " << parser->getValueAsFloat("volume") << "\n";
    std::cout << "name: " << parser->getValueAsString("fullscreen") << "\n";
    std::cout << "Done.\n\n";

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

    /*sf::Texture texture;
    if (!texture.loadFromFile("C:/Development/Liquid-Engine/solution/Debug/test.png"))
        return 0;*/

    liquid::utilities::Vertex2* vert0 = new liquid::utilities::Vertex2({ 20.0f, 20.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 0.0f, 0.0f });
    liquid::utilities::Vertex2* vert1 = new liquid::utilities::Vertex2({ 276.0f, 20.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 256.0f, 0.0f });
    liquid::utilities::Vertex2* vert2 = new liquid::utilities::Vertex2({ 276.0f, 276.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 256.0f, 256.0f });
    liquid::utilities::Vertex2* vert3 = new liquid::utilities::Vertex2({ 20.0f, 276.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 0.0f, 256.0f });
    //liquid::impl::SFMLRenderable* renderable = new liquid::impl::SFMLRenderable({ vert0,vert1,vert2,vert3 }, texture, 1.0f);
    //renderer->addRenderable(renderable);

    //sf::Vector2u texSize = texture.getSize();

    //liquid::impl::SFMLRenderableBatch* batch = new liquid::impl::SFMLRenderableBatch(texture, 3);
    liquid::common::Entity* entity1 = new liquid::common::Entity();
    liquid::common::Entity* entity2 = new liquid::common::Entity();
    liquid::common::Entity* entity3 = new liquid::common::Entity();

    entity1->setPosition(340.0f, 340.0f);
    entity2->setPosition(475.0f, 175.0f);
    entity3->setPosition(800.0f, 350.0f);

    scene->addEntity(entity1);
    scene->addEntity(entity2);
    scene->addEntity(entity3);

    /*entity1->setVerticesPtr(batch->nextVertices());
    entity2->setVerticesPtr(batch->nextVertices());
    entity3->setVerticesPtr(batch->nextVertices());*/
    //renderer->addRenderable(batch);

    liquid::navigation::NavGraph* graph = new liquid::navigation::NavGraph();
    graph->addNavNode(500.0f, 500.0f);
    graph->addNavNode(250.0f, 250.0f);
    graph->addNavEdge(0, 1);

    auto leftHandle = liquid::events::EventDispatcher<liquid::events::KeyboardEventData>::addListener(
        [&ent = entity1](const liquid::events::KeyboardEventData& evnt)->bool
    {
        if (evnt.mKeyCode == sf::Keyboard::A)
            ent->addPosition(-5.0f, 0.0f);
        else if (evnt.mKeyCode == sf::Keyboard::D)
            ent->addPosition(5.0f, 0.0f);
        else if (evnt.mKeyCode == sf::Keyboard::W)
            ent->addPosition(0.0f, -5.0f);
        else if (evnt.mKeyCode == sf::Keyboard::S)
            ent->addPosition(0.0f, 5.0f);
        else if (evnt.mKeyCode == sf::Keyboard::Escape)
            liquid::common::GameManager::instance().setGameRunning(false);

        return true;
    });

    sf::Texture texture2;
    if (!texture2.loadFromFile("C:/Development/Liquid-Engine/solution/Debug/smoke.png"))
        return 2;

    /*liquid::impl::SFMLRenderableBatch* particleBatch = new liquid::impl::SFMLRenderableBatch(texture2, 50);
    liquid::data::ParticleData* particleData = new liquid::data::ParticleData(liquid::data::ConfigurationParser());
    liquid::common::ParticleEmitter* emitter = new liquid::common::ParticleEmitter(*particleData, particleBatch, 50);
    emitter->setPosition(950.0f, 500.0f);
    emitter->setRepeat(false);
    renderer->addRenderable(particleBatch);
    scene->addEntity(emitter);

    auto mouseHandle = liquid::events::EventDispatcher<liquid::events::MouseEventData>::addListener(
        [&em = emitter](const liquid::events::MouseEventData& evnt)->bool
        {
            if (evnt.mMouseButton == sf::Mouse::Left && evnt.mPressed == true)
                em->emit();

            return true;
        }
    );*/

    /*liquid::utilities::Vertex2* vert4 = new liquid::utilities::Vertex2({ 0.0f, 0.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 0.0f, 0.0f });
    liquid::utilities::Vertex2* vert5 = new liquid::utilities::Vertex2({ 256.0f, 20.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 256.0f, 0.0f });
    liquid::utilities::Vertex2* vert6 = new liquid::utilities::Vertex2({ 256.0f, 256.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 256.0f, 256.0f });
    liquid::utilities::Vertex2* vert7 = new liquid::utilities::Vertex2({ 0.0f, 256.0f }, { 255.0f, 255.0f, 255.0f, 255.0f }, { 0.0f, 256.0f });
    liquid::impl::SFMLRenderable* renderable2 = new liquid::impl::SFMLRenderable({ vert4,vert5,vert6,vert7 }, texture2, 1.0f);
    renderer->addRenderable(renderable2);

    liquid::common::Particle* particle = new liquid::common::Particle(
        liquid::data::ParticleData(liquid::data::ConfigurationParser())
    );

    particle->setVerticesPtr({ vert4,vert5,vert6,vert7 });
    particle->emit(500.0f, 500.0f);
    scene->addEntity(particle);*/

    /*double val = 10;
    liquid::tweener::Tweener* tweener = new liquid::tweener::Tweener(val, 200.0, 20000.0,
        liquid::tweener::EasingFunction(liquid::tweener::EasingFuncs::bounce));

    liquid::utilities::DeltaTime::instance().start();
    while (tweener->isFinished() == false)
    {
        liquid::utilities::DeltaTime::instance().tick();
        tweener->update();
        std::cout << (val = tweener->getValue()) << std::endl;
    }*/

    liquid::common::GameManager::instance().execute();
    liquid::common::GameManager::instance().simulate();
    liquid::common::GameManager::instance().terminate();

    /*using namespace liquid::events;
    auto handle1 = EventDispatcher<KeyboardEventData>::
        addListener([](const KeyboardEventData& evnt)->bool
    {
        std::cout << "Keyboard Event Listener 1: " << evnt.mKeyCode << "\n";
        return true;
    });

    auto handle2 = EventDispatcher<KeyboardEventData>::
        addListener([](const KeyboardEventData& evnt)->bool
    {
        std::cout << "Keyboard Event Listener 2: " << evnt.mKeyCode << "\n";
        return true;
    });

    auto handle3 = EventDispatcher<WindowEventData>::
        addListener([](const WindowEventData& evnt)->bool
    {
        std::cout << "Window Event Listener 1:" << evnt.mEventType << "\n";
        return true;
    });

    std::cout << "Keyboard Event 1 ID: " << handle1 << std::endl;
    std::cout << "Keyboard Event 2 ID: " << handle2 << std::endl;
    std::cout << "Window Event 1 ID: " << handle3 << "\n\n";

    KeyboardEventData data1(32, true);
    KeyboardEventData data2(-1, true);
    WindowEventData data3(WindowEventData::eWindowEventType::WINDOWEVENT_CLOSED);

    EventDispatcher<KeyboardEventData>::triggerListeners(data1);
    EventDispatcher<KeyboardEventData>::triggerListeners(data2);
    EventDispatcher<WindowEventData>::triggerListeners(data3);

    std::cout << "\nNow removing second listener\n";
    EventDispatcher<KeyboardEventData>::removeListener(handle2);
    EventDispatcher<KeyboardEventData>::triggerListeners(data1);
    EventDispatcher<KeyboardEventData>::triggerListeners(data2);

    using namespace liquid::common;
    Entity* entity = new Entity();
    entity->setEntityUID("TestEntity");
    entity->setPosition(450.0f, 320.0f);
    int32_t resID = ResourceManager<Entity>::addResource(entity);

    KeyboardEventData kData(23, true);
    int32_t resID2 = ResourceManager<KeyboardEventData>::addResource(&kData);

    std::cout << "\nEntity Resource ID: " << resID << std::endl;
    std::cout << "Keyboard Data Resource ID: " << resID2 << "\n\n";

    Entity* retrieved = ResourceManager<Entity>::getResource(resID);
    std::cout << "\nENTITY DATA\nUID of " << retrieved->getEntityUID() << "\n";
    std::cout << "Position of " << retrieved->getPositionX() << ",";
    std::cout << retrieved->getPositionY() << "\n\n";

    using namespace liquid::utilities;
    int r1 = Random::instance().randomRange(5, 20);
    float r2 = Random::instance().randomRange(0.5f, 4.92f);
    std::array<float, 2> r3 = Random::instance().randomRange({ 5.2f,10.0f }, { 4.0f, 6.35f });
    std::array<float, 2> r4 = Random::instance().randomUnitVector();

    std::cout << "rand1 : " << r1 << std::endl;
    std::cout << "rand2 : " << r2 << std::endl;
    std::cout << "rand3 : " << r3.at(0) << ", " << r3.at(1) << std::endl;
    std::cout << "rand4 : " << r4.at(0) << ", " << r4.at(1) << "\n\n";

    std::string test;
    std::cin >> test;
    std::cout << "end";*/
}
