#include "RepeaterNode.h"

namespace liquid {
namespace ai {

    RepeaterNode::RepeaterNode() :
        DecoratorNode()
    {
        mRepeaterLimit = 0;
        mRepeaterCount = 0;
    }

    RepeaterNode::~RepeaterNode()
    {
    }

    void RepeaterNode::initialise()
    {
        BehaviourNode::initialise();
        mRepeaterCount = 0;
    }

    bool RepeaterNode::process()
    {
        if (mChildren.empty() == true)
            return true;

        bool result = mChildren[0]->process();
        
        if (mRepeaterLimit > 0)
        {
            if (result == true && mRepeaterCount >= mRepeaterLimit)
                return true;

            mRepeaterCount++;
        }

        return false;
    }

    void RepeaterNode::setRepeaterLimit(uint32_t limit)
    {
        mRepeaterLimit = limit;
    }

    const uint32_t RepeaterNode::getRepeaterLimit() const
    {
        return mRepeaterLimit;
    }

    const uint32_t RepeaterNode::getRepeaterCount() const
    {
        return mRepeaterCount;
    }

}}
