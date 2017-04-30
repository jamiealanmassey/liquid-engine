#include "RepeaterNode.h"

namespace liquid { namespace ai {
#ifndef _REPEATERCONDITIONALNODE_H
#define _REPEATERCONDITIONALNODE_H

class RepeaterConditionalNode : public RepeaterNode
{
public:
    RepeaterConditionalNode();
    ~RepeaterConditionalNode();

    virtual void initialise() override;
    virtual void process() override;
};

#endif // _REPEATERCONDITIONALNODE_H
}}
