#include "SelectorNode.h"

namespace liquid {
namespace ai {

    SelectorNode::SelectorNode() :
        BehaviourNode()
    {
        mNodeType = eBehaviourNodeType::NODETYPE_COMPOSITE;
        mCurrentlyProcessing = 0;
    }

    SelectorNode::~SelectorNode()
    {
    }

    void SelectorNode::initialise()
    {
        mCurrentlyProcessing = 0;
       
        if (mChildren.size() > 0)
            mChildren[mCurrentlyProcessing]->initialise();
        else
            mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
    }

    void SelectorNode::process()
    {
        eBehaviourNodeState state = mChildren[mCurrentlyProcessing]->getNodeState();

        if (state == eBehaviourNodeState::NODESTATE_SUCCESSFUL)
            mNodeState = eBehaviourNodeState::NODESTATE_SUCCESSFUL;
        else if (state == eBehaviourNodeState::NODESTATE_FAILURE)
        {
            mCurrentlyProcessing++;

            if (mCurrentlyProcessing == mChildren.size())
                mNodeState = eBehaviourNodeState::NODESTATE_FAILURE;
            else
                mChildren[mCurrentlyProcessing]->initialise();
        }
    }

    BehaviourNode* SelectorNode::nextNode()
    {
        if (mChildren.empty() == false && mCurrentlyProcessing != mChildren.size())
            return mChildren[mCurrentlyProcessing];
        else
            return nullptr;
    }

}}
