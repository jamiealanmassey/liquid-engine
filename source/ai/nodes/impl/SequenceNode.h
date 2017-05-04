#include "../base/CompositeNode.h"

namespace liquid { namespace ai {
#ifndef _SEQUENCENODE_H
#define _SEQUENCENODE_H

/**
 * \class SequenceNode
 *
 * \ingroup AI
 * \brief Visits each child in order with first to last, any fail and composite node will fail, if last 
 *        child succeeds then will return success to the parent
 *
 * \author Jamie Massey
 * \version 1.0
 * \date 04/05/2017
 *
 */

class SequenceNode : public CompositeNode
{
public:
    /// SequenceNode Constructor
    SequenceNode();

    /// SequenceNode Destructor
    ~SequenceNode();

    /// \brief Overload BehaviourNode::process, processes until a child fails
    virtual bool process() override;
};

#endif // _SEQUENCENODE_H
}}
