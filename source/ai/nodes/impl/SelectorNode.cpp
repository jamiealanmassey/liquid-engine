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

    bool SelectorNode::process()
    {
        for (BehaviourNode* node : mChildren)
        {
            if (node->process() == true)
                return true;
        }

        return false;
    }

}}
