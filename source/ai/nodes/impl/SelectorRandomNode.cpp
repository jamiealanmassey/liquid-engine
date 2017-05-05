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

    bool SelectorRandomNode::process(BehaviourContext* context)
    {
        for (BehaviourNode* node : getChildrenShuffled())
        {
            if (node->process(context) == true)
                return true;
        }

        return false;
    }

}}
