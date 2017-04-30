#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _INVERTERNODE_H
#define _INVERTERNODE_H

class InverterNode : public BehaviourNode
{
public:
    InverterNode();
    ~InverterNode();

    virtual void initialise() override;
    virtual void process() override;

    virtual void insertChild(BehaviourNode* node) override;
};

#endif // _INVERTERNODE_H
}}
