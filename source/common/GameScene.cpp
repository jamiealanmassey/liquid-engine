#include "GameScene.h"
#include "Entity.h"

namespace liquid {
namespace common {

    GameScene::GameScene()
    {
        mSceneName = "";
        //mSpatialManager = nullptr;
        mAllowUpdate = true;
        mAllowUpdateEvents = true;
        mAllowRenderer = true;
        mAllowPostProcesses = true;
    }

    GameScene::~GameScene()
    {}

    void GameScene::initialise()
    {

    }

    // TODO: Use LiquidEventData definition
    void GameScene::updateEvents()
    {
        
    }

    void GameScene::update()
    {
        if (mAllowUpdate == false)
            return;

        for (auto entity : mEntitiesBuffer)
        {
            mEntities.push_back(entity);
            mEntities.back()->setParentGameScene(this);
            mEntities.back()->initialise();

            // TODO: Add entity to the Spatial Manager if possible
        }

        mEntitiesBuffer.clear();
        // TODO: Update renderer

        for (auto entity : mEntities)
        {
            if (entity->getEntityState() == Entity::eEntityState::ENTITYSTATE_ACTIVE)
            {
                entity->updatePre();
                entity->update();
                entity->updatePost();
            }
        }

        /*if (mSpatialManager)
            mSpatialManager->update();*/

        std::vector<Entity*>::iterator it;
        for (it = mEntities.begin(); it != mEntities.end(); ++it)
        {
            if ((*it)->getEntityState() == Entity::eEntityState::ENTITYSTATE_DEAD)
            {
                it = mEntities.erase(it);
                if (it == mEntities.end())
                    break;
            }
        }

        // TODO: Render from given Renderer

    }

    void GameScene::addEntity(Entity* entity)
    {
        mEntitiesBuffer.push_back(entity);
    }

    void GameScene::addEntity(std::vector<Entity*> entities)
    {
        mEntitiesBuffer.insert(mEntitiesBuffer.begin(), entities.begin(), entities.end());
    }

    Entity* GameScene::getEntityAtPoint(float x, float y)
    {
        // TODO: Use spatial to make this more efficient
        for (auto entity : mEntities)
        {
            if (entity->isPointInside(x, y))
                return entity;
        }

        return nullptr;
    }

    Entity* GameScene::getEntityWithUID(std::string uid)
    {
        // TODO: Maybe make a lookup table?
        std::vector<Entity*>::iterator it = 
        std::find_if(mEntities.begin(), mEntities.end(),
            [&id = uid](const Entity* entity) {
            return entity->getEntityUID() == id;
        });

        return (*it);
    }

    /*void GameScene::setSpatialManager(Spatial* spatial)
    {
        mSpatialManager = spatial;
        mSpatialManager->initialise();
    }*/

    void GameScene::setAllowUpdate(bool isAllowed)
    {
        mAllowUpdate = isAllowed;
    }

    void GameScene::setAllowUpdateEvents(bool isAllowed)
    {
        mAllowUpdateEvents = isAllowed;
    }

    void GameScene::setAllowRenderer(bool isAllowed)
    {
        mAllowRenderer = isAllowed;
    }

    void GameScene::setAllowPostProcesses(bool isAllowed)
    {
        mAllowPostProcesses = isAllowed;
    }

    std::vector<Entity*>& GameScene::getEntities()
    {
        return mEntities;
    }

    std::string GameScene::getSceneName() const
    {
        return mSceneName;
    }

    /*Spatial* GameScene::getSpatialManager() const
    {
        return mSpatialManager;
    }*/

    bool GameScene::isAllowedUpdate() const
    {
        return mAllowUpdate;
    }

    bool GameScene::isAllowedUpdateEvents() const
    {
        return mAllowUpdateEvents;
    }

    bool GameScene::isAllowedRenderer() const
    {
        return mAllowRenderer;
    }

    bool GameScene::isAllowedPostProcesses() const
    {
        return mAllowPostProcesses;
    }

}}
