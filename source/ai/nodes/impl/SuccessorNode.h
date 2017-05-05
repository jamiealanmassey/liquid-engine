#include "../base/DecoratorNode.h"

namespace liquid { namespace ai {
#ifndef _SUCCESSORNODE_H
#define _SUCCESSORNODE_H

/**
 * \class SuccessorNode
 *
 * \ingroup AI
 * \brief Always returns success from the child node, regardless of actual result
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class SuccessorNode : public DecoratorNode
{
public:
    /// SuccessorNode Constructor
    SuccessorNode();

    /// SuccessorNode Destructor
    ~SuccessorNode();

    /// \brief Overload BehaviourNode::process, process always returns success
    virtual bool process(BehaviourContext* context) override;
};

#endif // _SUCCESSORNODE_H
}}
