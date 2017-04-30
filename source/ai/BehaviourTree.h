#include "BehaviourNode.h"

namespace liquid { namespace ai {
#ifndef _BEHAVIOURTREE_H
#define _BEHAVIOURTREE_H

class BehaviourTree
{
public:
    BehaviourTree();
    ~BehaviourTree();

    bool process();
    
    void setNodeRoot(BehaviourNode* node);

protected:
    BehaviourNode* mNodeRoot;
    BehaviourNode* mNodeCurrent;
};

#endif // _BEHAVIOURTREE_H
}}
