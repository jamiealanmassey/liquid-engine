#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _SUCCEEDERNODE_H
#define _SUCCEEDERNODE_H

class SucceederNode : public BehaviourNode
{
public:
    SucceederNode();
    ~SucceederNode();

    virtual void initialise() override;
    virtual void process() override;

    virtual void insertChild(BehaviourNode* node) override;
};

#endif // _SUCCEEDERNODE_H
}}
