#include "Entity.h"
#include "LuaManager.h"

namespace liquid {
namespace common {
    
    Entity::Entity() :
        mLuaFuncCreate(LuaManager::instance().getLuaState()),
        mLuaFuncUpdate(LuaManager::instance().getLuaState()),
        mLuaFuncKill(LuaManager::instance().getLuaState())
    {
        mFuncCallbackUpdate = nullptr;
        mFuncCallbackSetPosition = nullptr;
        mFuncCallbackAddPosition = nullptr;
        mFuncCallbackKilled = nullptr;
        mType = ENTITYTYPE_UNKNOWN;
        mState = eEntityState::ENTITYSTATE_ACTIVE;
        mPositionX = 0.0f;
        mPositionY = 0.0f;
        mOriginX = 0.5f;
        mOriginY = 0.5f;
        mWidth = 0.0f;
        mHeight = 0.0f;
        mUniqueID = "Invalid";
        mParentEntity = nullptr;
        mParentGameScene = nullptr;
        mAIAgent = nullptr;
        mVerticesCount = 4;

        mAtlasID = -1;
        mShaderID = -1;
        mBlendMode = 0;
        mVertices.resize(4);

        for (uint32_t i = 0; i < 4; i++)
            mVertices[i] = new utilities::Vertex2;
    }
    
    Entity::~Entity()
    {
        //destroyBox2D();
    }
    
    void Entity::initialise()
    {
        if (mLuaFuncCreate.isNil() == false)
            mLuaFuncCreate();
    }
    
    void Entity::updatePre()
    {
        // TODO: Box2D Body?
        
        
    }
    
    void Entity::update()
    {
        if (mFuncCallbackUpdate != nullptr)
            mFuncCallbackUpdate(this);

        if (mLuaFuncUpdate.isNil() == false)
            mLuaFuncUpdate();
    }
    
    void Entity::updatePost()
    {
        if (mAIAgent != nullptr)
            mAIAgent->update();
    }
    
    void Entity::setPosition(float x, float y)
    {
        mPositionX = x;
        mPositionY = y;
        
        float w = mVertices[1]->getTexCoord()[0] - mVertices[0]->getTexCoord()[0];
        float h = mVertices[2]->getTexCoord()[1] - mVertices[1]->getTexCoord()[1];

        float calcX = x - (mOriginX * w);
        float calcY = y - (mOriginY * h);

        mVertices[0]->setPosition(calcX, calcY);
        mVertices[1]->setPosition(calcX + w, calcY);
        mVertices[2]->setPosition(calcX + w, calcY + h);
        mVertices[3]->setPosition(calcX, calcY + h);

        for (auto child : mChildren)
            child->setPosition(x, y);

        if (mFuncCallbackSetPosition)
            mFuncCallbackSetPosition(mPositionX, mPositionY);
    }
    
    void Entity::addPosition(float x, float y)
    {
        mPositionX += x;
        mPositionY += y;
        
        mVertices[0]->setPosition(mVertices[0]->getPosition()[0] + x, 
                                  mVertices[0]->getPosition()[1] + y);

        mVertices[1]->setPosition(mVertices[1]->getPosition()[0] + x,
                                  mVertices[1]->getPosition()[1] + y);

        mVertices[2]->setPosition(mVertices[2]->getPosition()[0] + x,
                                  mVertices[2]->getPosition()[1] + y);

        mVertices[3]->setPosition(mVertices[3]->getPosition()[0] + x,
                                  mVertices[3]->getPosition()[1] + y);

        for (auto child : mChildren)
            child->setPosition(x, y);

        if (mFuncCallbackAddPosition)
            mFuncCallbackAddPosition(mPositionX, mPositionY);
    }

    void Entity::setSize(float w, float h)
    {
        mWidth = w;
        mHeight = h;

        setPosition(mPositionX, mPositionY);
    }

    void Entity::setTexCoords(float x, float y, float w, float h)
    {
        mVertices[0]->setTexCoord(x, y);
        mVertices[1]->setTexCoord(x + w, y);
        mVertices[2]->setTexCoord(x + w, y + h);
        mVertices[3]->setTexCoord(x, y + h);
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

        if (mLuaFuncKill.isNil() == false)
            mLuaFuncKill();
    }
    
    void Entity::setLuaScript(std::string luaScript)
    {
        mLuaScript = luaScript;
        lua_State* lua = LuaManager::instance().getLuaState();
        LuaManager::instance().executeScript(mLuaScript);

        mLuaFuncCreate = luabridge::getGlobal(lua, "create");
        mLuaFuncUpdate = luabridge::getGlobal(lua, "update");
        mLuaFuncKill = luabridge::getGlobal(lua, "kill");
    }

    void Entity::setParentGameScene(GameScene* scene, bool remove)
    {
        // TODO: This is an issue for removing in-between updates :/
        //if (mParentGameScene)
            // mParentGameScene->removeEntity(this);
        
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

    void Entity::createAIAgent()
    {
        if (mAIAgent)
            delete mAIAgent;

        mAIAgent = new ai::Agent();
        mAIAgent->setEntityPtr(this);
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
    
    void Entity::addVertex2(utilities::Vertex2* vertex)
    {
        mVertices.push_back(vertex);
        mVerticesCount++;
    }

    void Entity::removeVertex2(uint32_t index)
    {
        mVertices.erase(std::find(mVertices.begin(), mVertices.end(), mVertices[index]));
    }

    int32_t Entity::getEntityType() const
    {
        return mType;
    }
    
    Entity::eEntityState Entity::getEntityState() const
    {
        return mState;
    }

    const float Entity::getPositionX() const
    {
        return mPositionX;
    }
    
    const float Entity::getPositionY() const
    {
        return mPositionY;
    }
    
    const float Entity::getOriginX() const
    {
        return mOriginX;
    }

    const float Entity::getOriginY() const
    {
        return mOriginY;
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

    ai::Agent* Entity::getAIAgent() const
    {
        return mAIAgent;
    }

    std::vector<utilities::Vertex2*> Entity::getVertices()
    {
        return mVertices;
    }
    
    const uint32_t Entity::getVerticesCount() const
    {
        return mVertices.size();
    }

    void Entity::clearVertices()
    {
        mVertices.clear();
        mVerticesCount = 0;
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
