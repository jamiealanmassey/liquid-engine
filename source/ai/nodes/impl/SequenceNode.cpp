#include "SequenceNode.h"

namespace liquid {
namespace ai {

    SequenceNode::SequenceNode() :
        CompositeNode()
    {
    }

    SequenceNode::~SequenceNode()
    {
    }

    bool SequenceNode::process(BehaviourContext* context)
    {
        for (BehaviourNode* node : mChildren)
        {
            if (node->process(context) == false)
                return false;
        }

        return true;
    }

}}
