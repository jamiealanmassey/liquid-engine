#include "BehaviourTree.h"

namespace liquid {
namespace ai {

BehaviourTree::BehaviourTree() :
        BehaviourNode()
    {
        mNodeRoot = nullptr;
        mNodeCurrent = nullptr;
        mNodeType = eBehaviourNodeType::NODETYPE_COMPOSITE;
    }

    BehaviourTree::~BehaviourTree()
    {}

    void BehaviourTree::initialise()
    {
        mNodeCurrent = mNodeRoot;
        mNodeCurrent->initialise();

        while (mNodeCurrent->nextNode())
            mNodeCurrent = mNodeCurrent->nextNode();
    }

    void BehaviourTree::process()
    {
        if (mNodeCurrent->getParentNode() == nullptr && 
            mNodeCurrent->getNodeState() != eBehaviourNodeState::NODESTATE_PROCESSING)
        {
            mNodeState = mNodeCurrent->getNodeState();
        }

        BehaviourNode::eBehaviourNodeState state = mNodeCurrent->getNodeState();
        
        if (state == BehaviourNode::NODESTATE_PROCESSING)
        {
            mNodeCurrent->process();

            BehaviourNode* next = mNodeCurrent->nextNode();
            if (next != nullptr && next->getNodeState() == BehaviourNode::NODESTATE_PROCESSING)
                mNodeCurrent = next;
        }

        if (mNodeCurrent->getParentNode() &&
            mNodeCurrent->getNodeState() != BehaviourNode::NODESTATE_PROCESSING)
        {
            mNodeCurrent = mNodeCurrent->getParentNode();
        }
    }

    BehaviourNode* BehaviourTree::nextNode()
    {
        return mNodeCurrent;
    }

    void BehaviourTree::setNodeRoot(BehaviourNode* node)
    {
        mNodeRoot = node;
        initialise();
    }

    BehaviourNode* BehaviourTree::getNodeRoot()
    {
        return mNodeRoot;
    }

    BehaviourNode* BehaviourTree::getNodeCurrent()
    {
        return mNodeCurrent;
    }

}}
