#include "BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _BEHAVIOURTREE_H
#define _BEHAVIOURTREE_H

class BehaviourTree : public BehaviourNode
{
public:
    BehaviourTree();
    ~BehaviourTree();

    virtual void initialise() override;
    virtual void process() override;
    
    virtual BehaviourNode* nextNode();

    void setNodeRoot(BehaviourNode* node);

    BehaviourNode* getNodeRoot();
    BehaviourNode* getNodeCurrent();

protected:
    BehaviourNode* mNodeRoot;
    BehaviourNode* mNodeCurrent;
};

#endif // _BEHAVIOURTREE_H
}}
