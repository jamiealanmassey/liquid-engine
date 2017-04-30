#include <vector>
#include <algorithm>

namespace liquid { namespace ai {
#ifndef _BEHAVIOURNODE_H
#define _BEHAVIOURNODE_H

class BehaviourNode
{
public:
    enum eBehaviourNodeState
    {
        NODESTATE_PROCESSING = 0,
        NODESTATE_SUCCESSFUL = 1,
        NODESTATE_FAILURE = 2,
    };

    enum eBehaviourNodeType
    {
        NODETYPE_COMPOSITE = 0,
        NODETYPE_DECORATOR = 1,
        NODETYPE_LEAF = 2,
    };

public:
    BehaviourNode();
    ~BehaviourNode();

    virtual void initialise() = 0;
    virtual void process() = 0;

    virtual void insertChild(BehaviourNode* node);
    virtual void removeChild(BehaviourNode* node);

    virtual BehaviourNode* nextNode();

    void setParentNode(BehaviourNode* node);

    const eBehaviourNodeState getNodeState() const;
    const eBehaviourNodeType getNodeType() const;
    BehaviourNode* getParentNode();
    std::vector<BehaviourNode*> getChildren();

protected:
    eBehaviourNodeState mNodeState;
    eBehaviourNodeType mNodeType;
    BehaviourNode* mParentNode;
    std::vector<BehaviourNode*> mChildren;
};

#endif // _BEHAVIOURNODE_H
}}
