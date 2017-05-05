#include "LuaNode.h"

namespace liquid {
namespace ai {

    LuaNode::LuaNode(std::string luaScript) :
        LeafNode(),
        mLuaFuncInitialise(common::LuaManager::instance().getLuaState()),
        mLuaFuncProcess(common::LuaManager::instance().getLuaState())
    {
        setLuaScript(luaScript);
    }

    LuaNode::~LuaNode()
    {
    }

    void LuaNode::initialise()
    {
        BehaviourNode::initialise();

        if (mLuaFuncInitialise.isNil() == false)
            mLuaFuncInitialise();
    }

    bool LuaNode::process(BehaviourContext* context)
    {
        if (mLuaFuncProcess.isNil() == false)
            return mLuaFuncProcess(context);

        return false;
    }

    void LuaNode::setLuaScript(std::string luaScript)
    {
        mLuaScript = luaScript;
        lua_State* lua = common::LuaManager::instance().getLuaState();
        common::LuaManager::instance().executeScript(mLuaScript);

        mLuaFuncInitialise = luabridge::getGlobal(lua, "initialise");
        mLuaFuncProcess = luabridge::getGlobal(lua, "process");
    }

}}
