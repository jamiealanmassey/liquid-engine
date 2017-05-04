#include "DecoratorNode.h"

namespace liquid {
namespace ai {

    DecoratorNode::DecoratorNode() :
        BehaviourNode(eNodeType::NODETYPE_DECORATOR)
    {
    }

    DecoratorNode::~DecoratorNode()
    {
    }

    void DecoratorNode::insertChild(BehaviourNode* node)
    {
        if (mChildren.size() == 0)
            mChildren.push_back(node);
    }

    void DecoratorNode::removeChild(BehaviourNode* node)
    {
        if (mChildren.empty() == false)
            std::remove(mChildren.begin(), mChildren.end(), node);
    }

}}
