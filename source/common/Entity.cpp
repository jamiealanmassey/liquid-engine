#include "Entity.h"

namespace liquid {
namespace common {
    
    Entity::Entity()
    {
        mFuncCallbackSetPosition = nullptr;
        mFuncCallbackAddPosition = nullptr;
        mFuncCallbackKilled = nullptr;
        mType = ENTITYTYPE_UNKNOWN;
        mState = eEntityState::ENTITYSTATE_ACTIVE;
        mPositionX = 0.0f;
        mPositionY = 0.0f;
        mWidth = 0.0f;
        mHeight = 0.0f;
        mUniqueID = "Invalid";
        mParentEntity = nullptr;
        mParentGameScene = nullptr;
        mVerticesSet = false;
    }
    
    Entity::~Entity()
    {
        //destroyBox2D();
    }
    
    void Entity::initialise()
    {
        
    }
    
    void Entity::updatePre()
    {
        // TODO: DO THIS IN MANAGER, NOT HERE
        //if (m_EntityState != eEntityState::ENTITYSTATE_ALIVE)
            //return;
        
        // TODO: Box2D Body?
        
        
    }
    
    void Entity::update()
    {
        
    }
    
    void Entity::updatePost()
    {
        
    }
    
    void Entity::setPosition(float x, float y)
    {
        mPositionX = x;
        mPositionY = y;
        
        if (mVerticesSet)
        {
            mVerticesPtr[0]->setPosition(x, y);
            mVerticesPtr[1]->setPosition(x + mWidth, y);
            mVerticesPtr[2]->setPosition(x + mWidth, y + mHeight);
            mVerticesPtr[3]->setPosition(x, y + mHeight);
        }

        for (auto child : mChildren)
            child->setPosition(x, y);

        if (mFuncCallbackSetPosition)
            mFuncCallbackSetPosition(mPositionX, mPositionY);
    }
    
    void Entity::addPosition(float x, float y)
    {
        mPositionX += x;
        mPositionY += y;
        
        if (mVerticesSet)
        {
            mVerticesPtr[0]->setPosition(mVerticesPtr[0]->getPosition()[0] + x, 
                                         mVerticesPtr[0]->getPosition()[1] + y);

            mVerticesPtr[1]->setPosition(mVerticesPtr[1]->getPosition()[0] + x,
                                         mVerticesPtr[1]->getPosition()[1] + y);

            mVerticesPtr[2]->setPosition(mVerticesPtr[2]->getPosition()[0] + x,
                                         mVerticesPtr[2]->getPosition()[1] + y);

            mVerticesPtr[3]->setPosition(mVerticesPtr[3]->getPosition()[0] + x,
                                         mVerticesPtr[3]->getPosition()[1] + y);
        }

        for (auto child : mChildren)
            child->setPosition(x, y);

        if (mFuncCallbackAddPosition)
            mFuncCallbackAddPosition(mPositionX, mPositionY);
    }

    void Entity::setSize(float w, float h)
    {
        mWidth = w;
        mHeight = h;

        if (mVerticesSet)
        {
            mVerticesPtr[0]->setPosition(mPositionX, mPositionY);
            mVerticesPtr[1]->setPosition(mPositionX + mWidth, mPositionY);
            mVerticesPtr[2]->setPosition(mPositionX + mWidth, mPositionY + mHeight);
            mVerticesPtr[3]->setPosition(mPositionX, mPositionY + mHeight);
        }
    }
    
    bool Entity::isPointInside(float x, float y) const
    {
        return (x >= mPositionX && x <= mPositionX + mWidth &&
                y >= mPositionY && y <= mPositionY + mHeight);
    }
    
    void Entity::sleep()
    {
        if (mState != eEntityState::ENTITYSTATE_DEAD)
            mState = eEntityState::ENTITYSTATE_SLEEP;
    }
    
    void Entity::wake()
    {
        if (mState != eEntityState::ENTITYSTATE_DEAD)
            mState = eEntityState::ENTITYSTATE_ACTIVE;
    }
    
    void Entity::kill()
    {
        mState = eEntityState::ENTITYSTATE_DEAD;

        if (mFuncCallbackKilled)
            mFuncCallbackKilled();
    }
    
    void Entity::setParentGameScene(GameScene* scene, bool remove)
    {
        // TODO: This is an issue for removing in-between updates :/
        if (mParentGameScene)
            ;// mParentGameScene->removeEntity(this);
        
        mParentGameScene = scene;
    }
    
    void Entity::setParentEntity(Entity* entity)
    {
        if (entity == nullptr)
        {
            mParentEntity->removeChild(this);
            mParentEntity = nullptr;
            return;
        }
        
        mParentEntity = entity;
        mParentEntity->addChild(this);
    }
    
    void Entity::setEntityType(int32_t type)
    {
        mType = type;
    }
    
    void Entity::setEntityUID(std::string uid)
    {
        // TODO: Use UID Cache to stop name clashing
        mUniqueID = uid;
    }
    
    void Entity::setVerticesPtr(std::array<liquid::utilities::Vertex2*, 4> vertices)
    {
        mVerticesSet = true;
        mVerticesPtr = vertices;

        mWidth = mVerticesPtr[1]->getTexCoord()[0] - mVerticesPtr[0]->getTexCoord()[0];
        mHeight = mVerticesPtr[2]->getTexCoord()[1] - mVerticesPtr[1]->getTexCoord()[1];

        mVerticesPtr[0]->setPosition(mPositionX, mPositionY);
        mVerticesPtr[1]->setPosition(mPositionX + mWidth, mPositionY);
        mVerticesPtr[2]->setPosition(mPositionX + mWidth, mPositionY + mHeight);
        mVerticesPtr[3]->setPosition(mPositionX, mPositionY + mHeight);
    }

    int32_t Entity::getEntityType() const
    {
        return mType;
    }
    
    Entity::eEntityState Entity::getEntityState() const
    {
        return mState;
    }

    float Entity::getPositionX() const
    {
        return mPositionX;
    }
    
    float Entity::getPositionY() const
    {
        return mPositionY;
    }
    
    std::string Entity::getEntityUID() const
    {
        return mUniqueID;
    }
    
    std::vector<Entity*> Entity::getChildren() const
    {
        return mChildren;
    }
    
    Entity* Entity::getParentEntity() const
    {
        return mParentEntity;
    }
    
    GameScene* Entity::getParentGameScene() const
    {
        return mParentGameScene;
    }
    
    void Entity::addChild(Entity* entity)
    {
        mChildren.push_back(entity);
        entity->setPosition(entity->getPositionX() + mPositionX, 
                            entity->getPositionY() + mPositionY);
    }
    
    void Entity::removeChild(Entity* entity)
    {
        std::remove(mChildren.begin(), mChildren.end(), entity);
    }
    
}}
