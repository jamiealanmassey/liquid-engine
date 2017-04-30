#include "../BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _REPEATERNODE_H
#define _REPEATERNODE_H

class RepeaterNode : public BehaviourNode
{
public:
    RepeaterNode();
    ~RepeaterNode();

    virtual void initialise() override;
    virtual void process() override;

    virtual void insertChild(BehaviourNode* node) override;

    void setRepeaterLimit(uint32_t count);

    const uint32_t getRepeaterLimit() const;
    const uint32_t getRepeaterCount() const;

    void resetNextNode(BehaviourNode* node);

protected:
    uint32_t mRepeaterLimit;
    uint32_t mRepeaterCount;
};

#endif // _REPEATERNODE_H
}}
