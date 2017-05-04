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

    bool UntilSuccessNode::process()
    {
        if (mChildren.empty() == true)
            return true;

        if (mChildren[0]->process() == true)
            return true;
        else
            return false;
    }

}}
