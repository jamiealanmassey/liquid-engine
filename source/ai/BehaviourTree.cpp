#include "BehaviourTree.h"
#include "../common/LuaManager.h"

namespace liquid {
namespace ai {

BehaviourTree::BehaviourTree() /*:
        BehaviourNode()*/
    {
        mRootNode = nullptr;
        mContext = new BehaviourContext;

        //mNodeCurrent = nullptr;
        //mNodeType = eBehaviourNodeType::NODETYPE_COMPOSITE;
    }

    BehaviourTree::~BehaviourTree()
    {}

    /*void BehaviourTree::initialise()
    {
        mNodeCurrent = mNodeRoot;
        mNodeCurrent->initialise();

        while (mNodeCurrent->nextNode())
            mNodeCurrent = mNodeCurrent->nextNode();
    }*/

    bool BehaviourTree::process()
    {
        if (mRootNode != nullptr)
            return mRootNode->process(mContext);

        return true;
    }

    BehaviourNode* BehaviourTree::nextNode()
    {
        return nullptr;//mNodeCurrent;
    }

    void BehaviourTree::setNodeRoot(BehaviourNode* node)
    {
        mRootNode = node;
        mRootNode->initialise();
    }

    BehaviourNode* BehaviourTree::getNodeRoot()
    {
        return mRootNode;
    }

    BehaviourContext* BehaviourTree::getContext()
    {
        return mContext;
    }

    /*BehaviourNode* BehaviourTree::getNodeCurrent()
    {
        return mNodeCurrent;
    }*/

}}
