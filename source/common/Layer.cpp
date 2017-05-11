#include "Layer.h"

namespace liquid {
namespace common {

    Layer::Layer(GameScene* parentScene)
    {
        mParentScene = parentScene;
    }

    Layer::~Layer()
    {
        for (Entity* entity : mEntities)
            delete entity;

        mEntities.clear();
        mEntitiesBuffer.clear();
    }

    void Layer::update()
    {
        for (auto entity : mEntitiesBuffer)
        {
            mEntities.push_back(entity);
            mEntities.back()->setParentGameScene(mParentScene);
            mEntities.back()->initialise();

            // TODO: Add entity to the Spatial Manager if possible
        }

        mEntitiesBuffer.clear();

        for (auto entity : mEntities)
        {
            if (entity->getEntityState() == Entity::eEntityState::ENTITYSTATE_ACTIVE)
            {
                entity->updatePre();
                entity->update();
                entity->updatePost();
            }
        }

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
    }

    void Layer::insertEntity(Entity* entity)
    {
        mEntitiesBuffer.push_back(entity);
    }

    void Layer::insertEntity(std::vector<Entity*> entities)
    {
        mEntitiesBuffer.insert(mEntitiesBuffer.begin(), entities.begin(), entities.end());
    }

    void Layer::setSpatialHash(spatial::Spatial* spatialHash)
    {
        if (mSpatialHash != nullptr)
        {
            delete mSpatialHash;
            mSpatialHash = nullptr;
        }

        mSpatialHash = spatialHash;
    }

    void Layer::setParentScene(GameScene* gameScene)
    {
        mParentScene = gameScene;
    }

    spatial::Spatial* Layer::getSpatialHash() const
    {
        return mSpatialHash;
    }

    GameScene* Layer::getParentScene() const
    {
        return mParentScene;
    }

    std::vector<Entity*> Layer::getEntities() const
    {
        return mEntities;
    }

    std::vector<Entity*> Layer::getEntities(std::array<float, 4> region)
    {
        if (region[0] == 0 && region[1] == 0 && region[2] == 0 && region[3] == 0)
            return mEntities;

        if (mSpatialHash != nullptr)
        {
            float x1 = region[0];
            float y1 = region[1];
            float x2 = region[2] - region[0];
            float y2 = region[3] - region[1];

            return mSpatialHash->query({ x1, y1, x2, y2 });
        }

        return mEntities;
    }

    Entity* Layer::getEntityAtPoint(float x, float y)
    {
        for (auto entity : mEntities)
        {
            if (entity->isPointInside(x, y))
                return entity;
        }

        return nullptr;
    }

    Entity* Layer::getEntityAtPoint(float x, float y, std::array<float, 4> region)
    {
        if (mSpatialHash != nullptr)
        {
            float x1 = region[0];
            float y1 = region[1];
            float x2 = region[2] - region[0];
            float y2 = region[3] - region[1];

            std::vector<Entity*> entities = mSpatialHash->query({ x1, y1, x2, y2 });
            for (Entity* entity : entities)
            {
                if (entity->isPointInside(x, y))
                    return entity;
            }
        }

        return nullptr;
    }

    Entity* Layer::getEntityWithID(std::string uid)
    {
        // TODO: Maybe make a lookup table?
        std::vector<Entity*>::iterator it =
            std::find_if(mEntities.begin(), mEntities.end(),
                [&id = uid](const Entity* entity) {
            return entity->getEntityUID() == id;
        });

        return (*it);
    }

    Entity* Layer::getEntityWithID(std::string uid, std::array<float, 4> region)
    {
        if (mSpatialHash != nullptr)
        {
            float x1 = region[0];
            float y1 = region[1];
            float x2 = region[2] - region[0];
            float y2 = region[3] - region[1];

            std::vector<Entity*>::iterator it =
                std::find_if(mEntities.begin(), mEntities.end(),
                    [&id = uid](const Entity* entity) {
                return entity->getEntityUID() == id;
            });

            return (*it);
        }

        return nullptr;
    }

}}
