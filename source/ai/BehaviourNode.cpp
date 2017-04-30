#include "BehaviourNode.h"

namespace liquid {
namespace ai {

    BehaviourNode::BehaviourNode()
    {
        mNodeState = NODESTATE_PROCESSING;
        mNodeType = NODETYPE_LEAF;
        mParentNode = nullptr;
    }

    BehaviourNode::~BehaviourNode()
    {
        for (uint32_t i = 0; i < mChildren.size(); i++)
            delete mChildren[i];

        mChildren.clear();
    }

    void BehaviourNode::insertChild(BehaviourNode* node)
    {
        node->setParentNode(this);
        mChildren.push_back(node);
    }

    void BehaviourNode::removeChild(BehaviourNode* node)
    {
        if (node != nullptr)
        {
            std::remove(mChildren.begin(), mChildren.end(), node);
            node->setParentNode(nullptr);
        } 
    }

    BehaviourNode* BehaviourNode::nextNode()
    {
        if (mChildren.empty() == false)
            return mChildren[0];
        else
            return nullptr;
    }

    void BehaviourNode::setParentNode(BehaviourNode* node)
    {
        mParentNode = node;
    }

    const BehaviourNode::eBehaviourNodeState BehaviourNode::getNodeState() const
    {
        return mNodeState;
    }

    const BehaviourNode::eBehaviourNodeType BehaviourNode::getNodeType() const
    {
        return mNodeType;
    }

    BehaviourNode* BehaviourNode::getParentNode()
    {
        return mParentNode;
    }

    std::vector<BehaviourNode*> BehaviourNode::getChildren()
    {
        return mChildren;
    }

}}
