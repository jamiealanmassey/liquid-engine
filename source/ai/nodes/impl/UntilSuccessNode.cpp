#include "UntilSuccessNode.h"

namespace liquid {
namespace ai {

    UntilSuccessNode::UntilSuccessNode() :
        DecoratorNode()
    {
    }

    UntilSuccessNode::~UntilSuccessNode()
    {
    }

    bool UntilSuccessNode::process(BehaviourContext* context)
    {
        if (mChildren.empty() == true)
            return true;

        if (mChildren[0]->process(context) == true)
            return true;
        else
            return false;
    }

}}
