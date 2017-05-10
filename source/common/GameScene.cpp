#include "GameScene.h"
#include "Entity.h"

namespace liquid {
namespace common {

    GameScene::GameScene()
    {
        mSceneName = "";
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

    void GameScene::update()
    {
        if (mAllowUpdate == false)
            return;

        for (Layer* layer : mLayers)
            layer->update();

        for (auto animator : mAnimators)
            animator->update();
    }

    void GameScene::insertLayer(std::string name, Layer* layerPtr)
    {
        layerPtr->setParentScene(this);
        mLayers.push_back(layerPtr);
        mLayerIndexer[name] = mLayers.size() - 1;
    }

    void GameScene::removeLayer(std::string name)
    {
        std::map<std::string, uint32_t>::iterator it;
        if ((it = mLayerIndexer.find(name)) == mLayerIndexer.end())
            return;

        delete mLayers[mLayerIndexer[name]];
        mLayers.erase(mLayers.begin() + mLayerIndexer[name]);

        for (; it != mLayerIndexer.end(); ++it)
            (*it).second--;

        mLayerIndexer.erase(name);
    }

    Layer* GameScene::getLayer(std::string name)
    {
        if (mLayerIndexer.find(name) != mLayerIndexer.end())
            return mLayers[mLayerIndexer[name]];

        return nullptr;
    }

    Entity* GameScene::getEntityAtPoint(float x, float y)
    {
        Entity* entity = nullptr;
        for (Layer* layer : mLayers)
        {
            if ((entity = layer->getEntityAtPoint(x, y)) != nullptr)
                return entity;
        }

        return nullptr;
    }

    Entity* GameScene::getEntityWithUID(std::string uid)
    {
        Entity* entity = nullptr;
        for (Layer* layer : mLayers)
        {
            if ((entity = layer->getEntityWithID(uid)) != nullptr)
                return entity;
        }

        return nullptr;
    }

    void GameScene::addAnimator(animation::Animator* animator)
    {
        mAnimators.push_back(animator);
    }

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

    std::vector<Entity*> GameScene::getEntities()
    {
        std::vector<Entity*> entities;
        for (Layer* layer : mLayers)
        {
            std::vector<Entity*> layerEnts = layer->getEntities();
            entities.insert(entities.begin(), layerEnts.begin(), layerEnts.end());
        }

        return entities;
    }

    std::vector<Layer*> GameScene::getLayers()
    {
        return mLayers;
    }

    std::string GameScene::getSceneName() const
    {
        return mSceneName;
    }

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
