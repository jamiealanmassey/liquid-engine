#include "RepeaterNode.h"

namespace liquid {
namespace ai {

    RepeaterNode::RepeaterNode() :
        BehaviourNode()
    {
        mNodeType = eBehaviourNodeType::NODETYPE_DECORATOR;
        mRepeaterLimit = 0;
        mRepeaterCount = 0;
    }

    RepeaterNode::~RepeaterNode()
    {
    }

    void RepeaterNode::initialise()
    {
        mNodeState = eBehaviourNodeState::NODESTATE_PROCESSING;
        mRepeaterCount = 0;

        if (mChildren.size() > 0)
            mChildren[0]->initialise();
        else
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

    void RepeaterNode::process()
    {
        eBehaviourNodeState state = mChildren[0]->getNodeState();

        if (state == eBehaviourNodeState::NODESTATE_FAILURE ||
            state == eBehaviourNodeState::NODESTATE_SUCCESSFUL)
        {
            if (mRepeaterLimit > 0 && mRepeaterCount == mRepeaterLimit)
                mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
            else if (mRepeaterLimit > 0)
                mRepeaterCount++;
        }
    }

    void RepeaterNode::insertChild(BehaviourNode* node)
    {
        if (mChildren.empty() == true)
            BehaviourNode::insertChild(node);
    }

    void RepeaterNode::setRepeaterLimit(uint32_t count)
    {
        mRepeaterLimit = count;
    }

    const uint32_t RepeaterNode::getRepeaterLimit() const
    {
        return mRepeaterLimit;
    }

    const uint32_t RepeaterNode::getRepeaterCount() const
    {
        return mRepeaterCount;
    }

}}
