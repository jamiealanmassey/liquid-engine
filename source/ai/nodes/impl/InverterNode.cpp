#include "InverterNode.h"

namespace liquid {
namespace ai {

    InverterNode::InverterNode() :
        DecoratorNode()
    {
    }

    InverterNode::~InverterNode()
    {
    }

    bool InverterNode::process()
    {
        if (mChildren.empty() == false)
            return !mChildren[0]->process();

        return false;
    }

}}
