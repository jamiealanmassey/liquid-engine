#include "UntilFailNode.h"

namespace liquid {
namespace ai {

    UntilFailNode::UntilFailNode() :
        DecoratorNode()
    {
    }

    UntilFailNode::~UntilFailNode()
    {
    }

    bool UntilFailNode::process(BehaviourContext* context)
    {
        if (mChildren.empty() == true)
            return true;

        if (mChildren[0]->process(context) == false)
            return true;
        else
            return false;
    }

}}
