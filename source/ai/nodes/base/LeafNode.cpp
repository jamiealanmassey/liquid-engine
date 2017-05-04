#include "LeafNode.h"

namespace liquid {
namespace ai {

    LeafNode::LeafNode() :
        BehaviourNode(eNodeType::NODETYPE_LEAF)
    {
    }

    LeafNode::~LeafNode()
    {
    }

    void LeafNode::insertChild(BehaviourNode* node)
    {
    }

    void LeafNode::removeChild(BehaviourNode* node)
    {
    }

}}
