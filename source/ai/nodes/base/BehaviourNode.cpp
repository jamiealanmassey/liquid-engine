#include "BehaviourNode.h"

namespace liquid {
namespace ai {

    BehaviourNode::BehaviourNode(eNodeType type)
    {
        mNodeType = type;
    }

    BehaviourNode::~BehaviourNode()
    {

    }

    void BehaviourNode::initialise()
    {
        for (BehaviourNode* node : mChildren)
            node->initialise();
    }

    const BehaviourNode::eNodeType BehaviourNode::getNodeType() const
    {
        return mNodeType;
    }

    std::vector<BehaviourNode*> BehaviourNode::getChildren() const
    {
        return mChildren;
    }

    std::vector<BehaviourNode*> BehaviourNode::getChildrenShuffled() const
    {
        std::vector<BehaviourNode*> shuffled = mChildren;
        std::random_shuffle(shuffled.begin(), shuffled.end());
        return shuffled;
    }

}}
