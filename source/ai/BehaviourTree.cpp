#include "BehaviourTree.h"

namespace liquid {
namespace ai {

BehaviourTree::BehaviourTree() /*:
        BehaviourNode()*/
    {
        mRootNode = nullptr;
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
            return mRootNode->process();

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

    /*BehaviourNode* BehaviourTree::getNodeCurrent()
    {
        return mNodeCurrent;
    }*/

}}
