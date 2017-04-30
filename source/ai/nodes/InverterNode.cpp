#include "InverterNode.h"

namespace liquid {
namespace ai {

    InverterNode::InverterNode() :
        BehaviourNode()
    {
        mNodeType = eBehaviourNodeType::NODETYPE_DECORATOR;
    }

    InverterNode::~InverterNode()
    {
    }

    void InverterNode::initialise()
    {
        mNodeState = eBehaviourNodeState::NODESTATE_PROCESSING;

        if (mChildren.size() > 0)
            mChildren[0]->initialise();
        else
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

    void InverterNode::process()
    {
        eBehaviourNodeState state = mChildren[0]->getNodeState();

        if (state == eBehaviourNodeState::NODESTATE_FAILURE)
            mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
        else if (state == eBehaviourNodeState::NODESTATE_SUCCESSFUL)
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
    }

    void InverterNode::insertChild(BehaviourNode* node)
    {
        if (mChildren.empty() == true)
            BehaviourNode::insertChild(node);
    }

}}
