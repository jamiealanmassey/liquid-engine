#include "RepeaterConditionalNode.h"

namespace liquid {
namespace ai {

    RepeaterConditionalNode::RepeaterConditionalNode() :
        RepeaterNode()
    {
    }

    RepeaterConditionalNode::~RepeaterConditionalNode()
    {
    }

    void RepeaterConditionalNode::initialise()
    {
        mNodeState = eBehaviourNodeState::NODESTATE_PROCESSING;

        if (mChildren.size() > 0)
            mChildren[0]->initialise();

        mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

    void RepeaterConditionalNode::process()
    {
        eBehaviourNodeState state = mChildren[0]->getNodeState();

        if (state == eBehaviourNodeState::NODESTATE_SUCCESSFUL)
        {
            if (mRepeaterLimit > 0 && mRepeaterCount == mRepeaterLimit)
                mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
            else if (mRepeaterLimit > 0)
                mRepeaterCount++;
        }
        else if (state == eBehaviourNodeState::NODESTATE_FAILURE)
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

}}
