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

    bool UntilFailNode::process()
    {
        if (mChildren.empty() == true)
            return true;

        if (mChildren[0]->process() == false)
            return true;
        else
            return false;
    }

}}
