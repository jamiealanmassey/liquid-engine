#include "SelectorRandomNode.h"

namespace liquid {
namespace ai {

    SelectorRandomNode::SelectorRandomNode() :
        CompositeNode()
    {
    }

    SelectorRandomNode::~SelectorRandomNode()
    {
    }

    bool SelectorRandomNode::process()
    {
        for (BehaviourNode* node : getChildrenShuffled())
        {
            if (node->process() == true)
                return true;
        }

        return false;
    }

}}
