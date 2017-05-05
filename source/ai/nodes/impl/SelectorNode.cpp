#include "SelectorNode.h"

namespace liquid {
namespace ai {

    SelectorNode::SelectorNode() :
        CompositeNode()
    {
    }

    SelectorNode::~SelectorNode()
    {
    }

    bool SelectorNode::process(BehaviourContext* context)
    {
        for (BehaviourNode* node : mChildren)
        {
            if (node->process(context) == true)
                return true;
        }

        return false;
    }

}}
