#include "Tests.h"

void Tests::lighting()
{
    liquid::impl::SFMLLightingManager* manager = new liquid::impl::SFMLLightingManager(
        liquid::common::GameManager::instance().getSettingsClass(), { 0.f, 0.f, 0.f, 50.f });

    liquid::graphics::Light* light0 = new liquid::graphics::Light({ 600.0f, 500.0 }, { 255.f, 50.f, 50.f, 255.f }, .5f, 600.f);
    liquid::graphics::Light* light1 = new liquid::graphics::Light({ 1200.0f, 500.0 }, { 50.f, 255.f, 50.f, 255.f }, .5f, 600.f);
    liquid::graphics::Light* light2 = new liquid::graphics::Light({ 900.0f, 800.0 }, { 50.f, 50.f, 255.f, 255.f }, .5f, 600.f);
    liquid::common::GameManager::instance().getRendererClass()->setLightingManager(manager);
    
    manager->insertLight(light0);
    manager->insertLight(light1);
    manager->insertLight(light2);
}

void Tests::batchedSFMLRendering(sf::Texture& texture)
{
    liquid::graphics::Renderer* renderer = liquid::common::GameManager::instance().getRendererClass();
    liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();

    liquid::common::Entity* entity1 = new liquid::common::Entity();
    liquid::common::Entity* entity2 = new liquid::common::Entity();
    liquid::common::Entity* entity3 = new liquid::common::Entity();
    liquid::common::Layer* layer0 = new liquid::common::Layer(scene);

    entity1->setPosition(340.0f, 340.0f);
    entity2->setPosition(475.0f, 175.0f);
    entity3->setPosition(800.0f, 350.0f);

    layer0->insertEntity(entity1);
    layer0->insertEntity(entity2);
    layer0->insertEntity(entity3);

    scene->insertLayer("default", layer0);
    mEntity = entity1;

    auto leftHandle = liquid::events::EventDispatcher<liquid::events::KeyboardEventData>::addListener(
        [&ent = mEntity](const liquid::events::KeyboardEventData& evnt)->bool
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
}

void Tests::particles(sf::Texture& texture)
{
    liquid::graphics::Renderer* renderer = liquid::common::GameManager::instance().getRendererClass();
    liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();
    liquid::common::Layer* layer0 = new liquid::common::Layer(scene);

    liquid::parser::ParserConfig particleParser;
    particleParser.parseString(liquid::data::ParticleData::mDefaultParticle);

    liquid::data::ParticleData* particleData = new liquid::data::ParticleData(particleParser);
    liquid::common::ParticleEmitter* emitter = new liquid::common::ParticleEmitter(*particleData, layer0, 150);
    emitter->setPosition(950.0f, 500.0f);
    emitter->setRepeat(false);
    layer0->insertEntity(emitter);
    scene->insertLayer("default", layer0);
    mEmitter = emitter;

    auto mouseHandle = liquid::events::EventDispatcher<liquid::events::MouseEventData>::addListener(
        [&em = mEmitter](const liquid::events::MouseEventData& evnt)->bool
    {
        if (evnt.mMouseButton == sf::Mouse::Left && evnt.mPressed == true)
            em->emit();

        return true;
    }
    );
}

void Tests::events()
{
    liquid::graphics::Renderer* renderer = liquid::common::GameManager::instance().getRendererClass();
    liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();

    using namespace liquid::events;
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
    int32_t resID = ResourceManager<Entity>::addResource("entity", entity);

    KeyboardEventData kData(23, true);
    int32_t resID2 = ResourceManager<KeyboardEventData>::addResource("kEvent", &kData);

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
    std::cout << "end";
}

void Tests::navigation()
{
    liquid::navigation::NavGraph* graph = new liquid::navigation::NavGraph();
    graph->addNavNode(500.0f, 500.0f);
    graph->addNavNode(250.0f, 250.0f);
    graph->addNavNode(700.0f, 250.0f);
    graph->addNavNode(710.0f, 250.0f);
    graph->addNavNode(720.0f, 250.0f);
    graph->addNavNode(730.0f, 250.0f);

    graph->addNavEdge(0, 1);
    graph->addNavEdge(0, 2);
    graph->addNavEdge(0, 3);
    graph->addNavEdge(0, 4);
    graph->addNavEdge(0, 5);

    liquid::navigation::AStar* aStar = new liquid::navigation::AStar(graph);
    liquid::navigation::NavPath path = aStar->search(1, 4);

    while (path.isEmpty() == false)
        std::cout << "node : " << path.popFront().getNodeIndex() << std::endl;

    std::cout << std::endl;
}

void Tests::parserXML()
{
    liquid::parser::ParserXML* xmlParser = new liquid::parser::ParserXML;
    xmlParser->parseFile("atlas.xml");
    xmlParser->dumpXMLTreeToFile();

    liquid::parser::ParserXML atlasParser;
    atlasParser.parseFile("atlas.xml");
    liquid::data::TextureAtlas* atlas = new liquid::data::TextureAtlas(atlasParser);
    atlas->compile();

    liquid::parser::ParserNodeSearch nodeSearch(atlasParser.getRootParserNode());
    std::list<liquid::parser::ParserNode*> names = nodeSearch.findParserNodes("name");

    nodeSearch.traverseChild("region");
    nodeSearch.traverseChild("name");

    liquid::parser::ParserNode* curNode = nodeSearch.getCurrentNode();
}

void Tests::quadTree()
{
    std::vector<liquid::common::Entity*> entities;
    entities.resize(150);
    for (uint32_t i = 0; i < 150; i++)
    {
        float posX = liquid::utilities::Random::instance().randomRange(100.0f, 500.0f);
        float posY = liquid::utilities::Random::instance().randomRange(100.0f, 500.0f);

        entities[i] = new liquid::common::Entity();
        entities[i]->setPosition(posX, posY);
    }

    liquid::spatial::QuadTree* quadTree =
        new liquid::spatial::QuadTree(4, { 300.0f,300.0f }, { 600.0f, 600.0f });

    for (int32_t i = 0; i < 150; i++)
        quadTree->insertEntity(entities[i]);

    for (int32_t i = 0; i < 20; i++)
        quadTree->removeEntity(entities[i]);

    quadTree->pruneDeadBranches();
    std::vector<liquid::common::Entity*> query = quadTree->query({ 0.0f, 0.0f, 600.0f, 600.0f });
}

void Tests::animation(sf::Texture& texture)
{
    //liquid::impl::SFMLRenderableBatch* batch = new liquid::impl::SFMLRenderableBatch(texture, 500);
    liquid::parser::ParserXML animXMLParser;
    liquid::parser::ParserXML atlasXMLParser;

    animXMLParser.parseFile("animation.xml");
    atlasXMLParser.parseFile("atlas.xml");
    atlasXMLParser.dumpXMLTreeToFile();

    liquid::data::TextureAtlas atlas(atlasXMLParser);
    liquid::animation::AnimationParser animParser(animXMLParser, atlas);

    liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();
    liquid::common::Layer* layer0 = new liquid::common::Layer(scene);

    for (uint32_t i = 0; i < 500; i++)
    {
        //std::array<liquid::utilities::Vertex2*, 4> vertices = batch->nextVertices();
        liquid::common::Entity* player = new liquid::common::Entity();
        liquid::animation::Animator* animator = new liquid::animation::Animator(animParser);
        //player->setVerticesPtr(vertices);

        /*liquid::animation::Animation animation;

        animation.push_back(liquid::animation::AnimationFrame({ 0,0 }, { 130,0 }, { 130, 150 }, { 0,150 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 130,0 }, { 260,0 }, { 260, 150 }, { 130,150 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 260,0 }, { 390,0 }, { 390, 150 }, { 260,150 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 390,0 }, { 520,0 }, { 520, 150 }, { 390,150 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 520,0 }, { 650,0 }, { 650, 150 }, { 520,150 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 650,0 }, { 780,0 }, { 780, 150 }, { 650,150 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 780,0 }, { 910,0 }, { 910, 150 }, { 780,150 }, 35.0f));
    
        animation.push_back(liquid::animation::AnimationFrame({ 0,150 }, { 130,150 }, { 130, 300 }, { 0,300 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 130,150 }, { 260,150 }, { 260, 300 }, { 130,300 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 260,150 }, { 390,150 }, { 390, 300 }, { 260,300 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 390,150 }, { 520,150 }, { 520, 300 }, { 390,300 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 520,150 }, { 650,150 }, { 650, 300 }, { 520,300 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 650,150 }, { 780,150 }, { 780, 300 }, { 650,300 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 780,150 }, { 910,150 }, { 910, 300 }, { 780,300 }, 35.0f));

        animation.push_back(liquid::animation::AnimationFrame({ 0,300 }, { 130,300 }, { 130, 450 }, { 0,450 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 130,300 }, { 260,300 }, { 260, 450 }, { 130,450 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 260,300 }, { 390,300 }, { 390, 450 }, { 260,450 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 390,300 }, { 520,300 }, { 520, 450 }, { 390,450 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 520,300 }, { 650,300 }, { 650, 450 }, { 520,450 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 650,300 }, { 780,300 }, { 780, 450 }, { 650,450 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 780,300 }, { 910,300 }, { 910, 450 }, { 780,450 }, 35.0f));

        animation.push_back(liquid::animation::AnimationFrame({ 0,450 }, { 130,450 }, { 130, 600 }, { 0,600 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 130,450 }, { 260,450 }, { 260, 600 }, { 130,600 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 260,450 }, { 390,450 }, { 390, 600 }, { 260,600 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 390,450 }, { 520,450 }, { 520, 600 }, { 390,600 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 520,450 }, { 650,450 }, { 650, 600 }, { 520,600 }, 35.0f));
        animation.push_back(liquid::animation::AnimationFrame({ 650,450 }, { 780,450 }, { 780, 600 }, { 650,600 }, 35.0f));

        animator->insertAnimation("run", animation);*/
        std::vector<liquid::utilities::Vertex2*> verts = player->getVertices();

        animator->transformAnimation("run");
        animator->setVerticesPtr({ verts[0],verts[1],verts[2],verts[3] });
        player->mTextureName = "player";

        // liquid::common::GameManager::instance().peekGameSceneFront()->insertLayer(player);
        //liquid::common::GameManager::instance().peekGameSceneFront()->addAnimator(animator);
        layer0->insertEntity(player);
        scene->addAnimator(animator);

        float positionX = liquid::utilities::Random::instance().randomRange(0.0f, 1850.0f);
        float positionY = liquid::utilities::Random::instance().randomRange(0.0f, 950.0f);
        player->setPosition(positionX, positionY);
    }

    scene->insertLayer("default", layer0);
}

void Tests::ai(sf::Texture& texture)
{
    liquid::graphics::Renderer* renderer = liquid::common::GameManager::instance().getRendererClass();
    liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();
    liquid::common::Layer* layer0 = new liquid::common::Layer(scene);

    //liquid::impl::SFMLRenderableBatch* renderable = new liquid::impl::SFMLRenderableBatch(texture, 2);
    liquid::parser::ParserXML animXMLParser;
    liquid::parser::ParserXML atlasXMLParser;

    animXMLParser.parseFile("animation.xml");
    atlasXMLParser.parseFile("player.atlas");
    atlasXMLParser.dumpXMLTreeToFile();

    liquid::data::TextureAtlas atlas(atlasXMLParser);
    liquid::animation::AnimationParser animParser(animXMLParser, atlas);

    liquid::animation::Animator* animator0 = new liquid::animation::Animator(animParser);
    liquid::animation::Animator* animator1 = new liquid::animation::Animator(animParser);

    liquid::common::Entity* entity0 = new liquid::common::Entity();
    liquid::common::Entity* entity1 = new liquid::common::Entity();

    int32_t resID = liquid::common::ResourceManager<liquid::data::TextureAtlas>::getResourceID("player");
    entity0->mAtlasID = resID;
    entity1->mAtlasID = resID;

    std::vector<liquid::utilities::Vertex2*> entity0Verts = entity0->getVertices();
    std::vector<liquid::utilities::Vertex2*> entity1Verts = entity1->getVertices();

    entity0->createAIAgent();
    entity1->createAIAgent();
    entity0->setEntityUID("entity0");
    entity1->setEntityUID("entity1");

    animator0->setVerticesPtr({ entity0Verts[0], entity0Verts[1], entity0Verts[2], entity0Verts[3] });
    animator1->setVerticesPtr({ entity1Verts[0], entity1Verts[1], entity1Verts[2], entity1Verts[3] });
    animator0->transformAnimation("run");
    animator1->transformAnimation("run");

    entity0->getAIAgent()->setMaxVelocity(.75f);
    entity1->getAIAgent()->setMaxVelocity(.5f);
    entity0->setPosition(500.0f, 500.0f);
    entity1->setPosition(800.0f, 800.0f);

    entity0->getAIAgent()->setVelocityX(1.0f);
    entity0->getAIAgent()->setVelocityY(1.25f);
    entity1->getAIAgent()->setVelocityX(-1.5f);
    entity1->getAIAgent()->setVelocityY(-1.0f);

    liquid::ai::BehaviourTree* tree = new liquid::ai::BehaviourTree();
    liquid::ai::RepeaterNode* node0 = new liquid::ai::RepeaterNode();
    liquid::ai::LuaNode* node1 = new liquid::ai::LuaNode("entity0.lua");
    node0->setRepeaterLimit(0);
    node0->insertChild(node1);
    tree->setNodeRoot(node0);
    entity0->getAIAgent()->setBehaviourTree(tree);

    //entity0->setLuaScript("entity0.lua");
    entity1->setLuaScript("entity1.lua");

    /*entity0->mFuncCallbackUpdate = [](liquid::common::Entity* entity) {
        if (entity->getAIAgent())
        {
            liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();
            liquid::graphics::Renderer* renderer = liquid::common::GameManager::instance().getRendererClass();

            liquid::ai::Agent* agent = entity->getAIAgent();
            liquid::ai::Agent* agent1 = scene->getEntityWithUID("entity1")->getAIAgent();

            agent->getSteeringManager()->wander();
            agent->getSteeringManager()->evade(agent1);

            float velocityX = agent->getVelocityX() * liquid::utilities::DeltaTime::DELTA;
            float velocityY = agent->getVelocityY() * liquid::utilities::DeltaTime::DELTA;
            entity->addPosition(velocityX, velocityY);

            float positionX = entity->getPositionX();
            float positionY = entity->getPositionY();
            static_cast<liquid::impl::SFMLRenderer*>(renderer)->getCamera()->setCentre({ positionX + 128.f, positionY + 128.f });
        }
    };

    entity1->mFuncCallbackUpdate = [](liquid::common::Entity* entity) {
        liquid::common::GameScene* scene = liquid::common::GameManager::instance().peekGameSceneFront();

        liquid::ai::Agent* agent0 = entity->getAIAgent();
        liquid::ai::Agent* agent1 = scene->getEntityWithUID("entity0")->getAIAgent();

        if (agent0 && agent1)
        {
            agent0->getSteeringManager()->pursue(agent1);
            
            float velocityX = agent0->getVelocityX() * liquid::utilities::DeltaTime::DELTA;
            float velocityY = agent0->getVelocityY() * liquid::utilities::DeltaTime::DELTA;
            entity->addPosition(velocityX, velocityY);
        }
    };*/

    //renderer->addRenderable(renderable);
    layer0->insertEntity(entity0);
    layer0->insertEntity(entity1);
    scene->insertLayer("default", layer0);
    scene->addAnimator(animator0);
    scene->addAnimator(animator1);
}
