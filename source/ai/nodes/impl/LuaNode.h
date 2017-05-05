extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include "../../../common/LuaManager.h"
#include "../base/LeafNode.h"

namespace liquid { namespace ai {
#ifndef _LUANODE_H
#define _LUANODE_H

/**
 * \class LuaNode
 *
 * \ingroup AI
 * \brief Specialised LeafNode that calls a bound Lua script when the tree reaches the node
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class LuaNode : public LeafNode
{
public:
    /** \brief LuaNode Constructor
      * \param luaScript Initial lua script loaded for this node, calls LuaNode::setLuaScript
      */
    LuaNode(std::string luaScript);

    /// LuaNode Destructors
    ~LuaNode();

    /// \brief Called when the parent node is initialised
    virtual void initialise() override;

    /** \brief Called to process the current node, takes the result of the lua function for success or fail
      * \return Gives a result of true if the script was successful, otherwise false
      */
    virtual bool process(BehaviourContext* context) override;

    /** \brief Sets the Lua script for this LuaNode, assigns LuaRef objects
      * \param luaScript Path + filename.lua to script to be loaded
      */
    void setLuaScript(std::string luaScript);

protected:
    std::string       mLuaScript;         ///< Name of the Lua script
    luabridge::LuaRef mLuaFuncInitialise; ///< LuaRef to lua function called when LuaNode::initialise is called
    luabridge::LuaRef mLuaFuncProcess;    ///< LuaRef to lua function called to process the node
};

#endif // _LUANODE_H
}}
