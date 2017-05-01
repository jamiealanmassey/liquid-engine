#include "RepeaterNode.h"

namespace liquid { namespace ai {
#ifndef _REPEATERCONDITIONALNODE_H
#define _REPEATERCONDITIONALNODE_H

/**
 * \class RepeaterNodeConditional
 *
 * \ingroup AI
 * \brief Similar to a RepeaterNode, except it will stop when the child BehaviourNode returns failure
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 01/05/2017
 *
 */

class RepeaterConditionalNode : public RepeaterNode
{
public:
    /// RepeaterConditionalNode Constructor
    RepeaterConditionalNode();

    /// RepeaterConditionalNode Destructor
    ~RepeaterConditionalNode();

    /// Overrides BehaviourNode::initialise
    virtual void initialise() override;

    /// Overrides BehaviourNode::process
    virtual void process() override;
};

#endif // _REPEATERCONDITIONALNODE_H
}}
