#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _SEQUENCENODE_H
#define _SEQUENCENODE_H

class SequenceNode : public BehaviourNode
{
public:
    SequenceNode();
    ~SequenceNode();

    virtual void initialise() override;
    virtual void process() override;

    virtual BehaviourNode* nextNode() override;

protected:
    uint32_t mCurrentlyProcessing;
};

#endif // _SEQUENCENODE_H
}}
