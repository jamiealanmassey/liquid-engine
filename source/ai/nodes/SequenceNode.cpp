#include "SequenceNode.h"

namespace liquid {
namespace ai {

    SequenceNode::SequenceNode() :
        BehaviourNode()
    {
        mNodeType = eBehaviourNodeType::NODETYPE_COMPOSITE;
        mCurrentlyProcessing = 0;
    }

    SequenceNode::~SequenceNode()
    {
    }

    void SequenceNode::initialise()
    {
        mCurrentlyProcessing = 0;
        mNodeState = eBehaviourNodeState::NODESTATE_PROCESSING;

        if (mChildren.size() > 0)
            mChildren[mCurrentlyProcessing]->initialise();
        else
            mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
    }

    void SequenceNode::process()
    {
        eBehaviourNodeState state = mChildren[mCurrentlyProcessing]->getNodeState();

        if (state == eBehaviourNodeState::NODESTATE_FAILURE)
            mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
        else if (state == eBehaviourNodeState::NODESTATE_SUCCESSFUL)
        {
            mCurrentlyProcessing++;

            if (mCurrentlyProcessing == mChildren.size())
                mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
            else
                mChildren[mCurrentlyProcessing]->initialise();
        }
    }

    BehaviourNode* SequenceNode::nextNode()
    {
        if (mChildren.empty() == false && mCurrentlyProcessing != mChildren.size())
            return mChildren[mCurrentlyProcessing];
        else
            return nullptr;
    }

}}
