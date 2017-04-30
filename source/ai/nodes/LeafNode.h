#include "../BehaviourNode.h"
#include <functional>

namespace liquid { namespace ai {
#ifndef _LEAFNODE_H
#define _LEAFNODE_H

class LeafNode : public BehaviourNode
{
public:
    typedef std::function<uint32_t()> BehaviourFunc;

public:
    LeafNode();
    ~LeafNode();

    virtual void initialise() override;
    virtual void process() override;

    virtual void insertChild(BehaviourNode* node) override;
    virtual void removeChild(BehaviourNode* node) override;

    virtual BehaviourNode* nextNode() override;

    void setFuncInitialise(BehaviourFunc func);
    void setFuncProcess(BehaviourFunc func);

protected:
    BehaviourFunc mFuncInitialise;
    BehaviourFunc mFuncProcess;
};

#endif // _LEAFNODE_H
}}
