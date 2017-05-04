#include "CompositeNode.h"

namespace liquid {
namespace ai {

    CompositeNode::CompositeNode() :
        BehaviourNode(eNodeType::NODETYPE_COMPOSITE)
    {
    }

    CompositeNode::~CompositeNode()
    {
    }

    void CompositeNode::insertChild(BehaviourNode* node)
    {
        mChildren.push_back(node);
    }

    void CompositeNode::removeChild(BehaviourNode* node)
    {
        std::remove(mChildren.begin(), mChildren.end(), node);
    }

}}
