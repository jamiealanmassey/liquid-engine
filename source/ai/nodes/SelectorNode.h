#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _SELECTORNODE_H
#define _SELECTORNODE_H

class SelectorNode : public BehaviourNode
{
public:
    SelectorNode();
    ~SelectorNode();

    virtual void initialise() override;
    virtual void process() override;

    virtual BehaviourNode* nextNode() override;

protected:
    uint32_t mCurrentlyProcessing;
};

#endif // _SELECTORNODE_H
}}
