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

    bool SequenceNode::process()
    {
        for (BehaviourNode* node : mChildren)
        {
            if (node->process() == false)
                return false;
        }

        return true;
    }

}}
