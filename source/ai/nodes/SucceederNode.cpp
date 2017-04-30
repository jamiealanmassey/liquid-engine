#include "SucceederNode.h"

namespace liquid {
namespace ai {

    SucceederNode::SucceederNode() :
        BehaviourNode()
    {
        mNodeType = eBehaviourNodeType::NODETYPE_DECORATOR;
    }

    SucceederNode::~SucceederNode()
    {
    }

    void SucceederNode::initialise()
    {
        if (mChildren.size() > 0)
            mChildren[0]->initialise();
        else
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

    void SucceederNode::process()
    {
        eBehaviourNodeState state = mChildren[0]->getNodeState();

        if (state == eBehaviourNodeState::NODESTATE_FAILURE ||
            state == eBehaviourNodeState::NODESTATE_SUCCESSFUL)
        {
            mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
        }
    }

    void SucceederNode::insertChild(BehaviourNode* node)
    {
        if (mChildren.empty() == true)
            BehaviourNode::insertChild(node);
    }

}}
