#include "BehaviourTree.h"

namespace liquid {
namespace ai {

    BehaviourTree::BehaviourTree()
    {
        mNodeRoot = nullptr;
        mNodeCurrent = nullptr;
    }

    BehaviourTree::~BehaviourTree()
    {}

    bool BehaviourTree::process()
    {
        if (mNodeCurrent->getParentNode() == nullptr)
            return true;

        BehaviourNode::eBehaviourNodeState state = mNodeCurrent->getNodeState();
        
        if (state == BehaviourNode::NODESTATE_PROCESSING)
        {
            mNodeCurrent->process();

            BehaviourNode* next = mNodeCurrent->nextNode();
            if (next != nullptr && next->getNodeState() == BehaviourNode::NODESTATE_PROCESSING)
                mNodeCurrent = next;
        }
        else if (state != BehaviourNode::NODESTATE_PROCESSING)
            mNodeCurrent = mNodeCurrent->getParentNode();

        return false;
    }

    void BehaviourTree::setNodeRoot(BehaviourNode* node)
    {
        mNodeRoot = node;
        mNodeCurrent = node;
        mNodeCurrent->initialise();

        while (mNodeCurrent->nextNode())
            mNodeCurrent = mNodeCurrent->nextNode();
    }

}}
