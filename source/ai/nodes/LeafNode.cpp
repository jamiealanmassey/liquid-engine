#include "LeafNode.h"

namespace liquid {
namespace ai {

    LeafNode::LeafNode() :
        BehaviourNode()
    {
        mFuncInitialise = nullptr;
        mFuncProcess = nullptr;
    }

    LeafNode::~LeafNode()
    {
    }

    void LeafNode::initialise()
    {
        if (mFuncInitialise)
            mFuncInitialise();
    }

    void LeafNode::process()
    {
        if (mFuncProcess)
        {
            uint32_t result = mFuncProcess();

            if (result == 1)
                mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
            else if (result == 2)
                mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
        }
        else
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

    void LeafNode::insertChild(BehaviourNode* node) {}
    void LeafNode::removeChild(BehaviourNode* node) {}

    BehaviourNode* LeafNode::nextNode()
    {
        return nullptr;
    }

    void LeafNode::setFuncInitialise(BehaviourFunc func)
    {
        mFuncInitialise = func;
    }

    void LeafNode::setFuncProcess(BehaviourFunc func)
    {
        mFuncProcess = func;
    }

}}
